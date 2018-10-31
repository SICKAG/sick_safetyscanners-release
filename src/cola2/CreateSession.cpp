// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------

/*!
*  Copyright (C) 2018, SICK AG, Waldkirch
*  Copyright (C) 2018, FZI Forschungszentrum Informatik, Karlsruhe, Germany
*
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.

*/

// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!
 * \file CreateSession.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/cola2/CreateSession.h>

#include <sick_safetyscanners/cola2/Cola2Session.h>
#include <sick_safetyscanners/cola2/Command.h>

namespace sick {
namespace cola2 {

CreateSession::CreateSession(Cola2Session& session)
  : Command(session, 0x4F, 0x58) // see cola2 manual 0x4F = O, 0x58 = X
{
  m_writer_ptr = std::make_shared<sick::data_processing::ReadWriteHelper>();
}

void CreateSession::addTelegramData(sick::datastructure::PacketBuffer::VectorBuffer& telegram) const
{
  uint8_t* data_ptr = prepareTelegramAndGetDataPtr(telegram);
  writeHeartbeatTimeoutToDataPtr(data_ptr);
  writeClientIdToDataPtr(data_ptr);
}

uint8_t* CreateSession::prepareTelegramAndGetDataPtr(
  sick::datastructure::PacketBuffer::VectorBuffer& telegram) const
{
  uint16_t prevSize = telegram.size();
  telegram.resize(prevSize + 5);
  return telegram.data() + prevSize;
}

bool CreateSession::canBeExecutedWithoutSessionID() const
{
  return true;
}

bool CreateSession::processReply()
{
  if ((getCommandType() == 'O' && getCommandMode() == 'A') ||
      (getCommandType() == 0x4F && getCommandMode() == 0x41))
  {
    m_session.setSessionID(getSessionID());
    ROS_INFO("Successfully opened Cola2 session with sessionID: %u", m_session.getSessionID());
    return true;
  }
  else
  {
    ROS_WARN("Could not open Cola2 session");
    return false;
  }
}

void CreateSession::writeHeartbeatTimeoutToDataPtr(uint8_t*& data_ptr) const
{
  uint8_t heartBeatTimeoutSeconds = 60;
  m_writer_ptr->writeuint8_tBigEndian(data_ptr, heartBeatTimeoutSeconds, 0);
}

void CreateSession::writeClientIdToDataPtr(uint8_t*& data_ptr) const
{
  uint32_t clientID = 1; // can be any random number
  m_writer_ptr->writeuint32_tBigEndian(data_ptr, clientID, 1);
}

} // namespace cola2
} // namespace sick
