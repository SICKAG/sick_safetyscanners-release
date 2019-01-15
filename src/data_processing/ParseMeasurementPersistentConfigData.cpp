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
 * \file ParseMeasurementPersistentConfigData.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2019-01-07
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/data_processing/ParseMeasurementPersistentConfigData.h>

#include <sick_safetyscanners/cola2/Command.h>

namespace sick {
namespace data_processing {

ParseMeasurementPersistentConfigData::ParseMeasurementPersistentConfigData()
{
  m_reader_ptr = std::make_shared<sick::data_processing::ReadWriteHelper>();
}


bool ParseMeasurementPersistentConfigData::parseTCPSequence(
  const datastructure::PacketBuffer& buffer, datastructure::FieldData& field_data) const
{
  const uint8_t* data_ptr(buffer.getBuffer().data());
  field_data.setStartAngle(readStartAngle(data_ptr));
  return true;
}

uint32_t ParseMeasurementPersistentConfigData::readStartAngle(const uint8_t* data_ptr) const
{
  return m_reader_ptr->readuint32_tLittleEndian(data_ptr, 16);
}

} // namespace data_processing
} // namespace sick
