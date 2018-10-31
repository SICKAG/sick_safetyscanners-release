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
 * \file SickSafetyscanners.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------


#include "sick_safetyscanners/SickSafetyscanners.h"

namespace sick {

SickSafetyscanners::SickSafetyscanners(
  packetReceivedCallbackFunction newPacketReceivedCallbackFunction,
  sick::datastructure::CommSettings settings)
  : m_newPacketReceivedCallbackFunction(newPacketReceivedCallbackFunction)
{
  ROS_INFO("Starting SickSafetyscanners");
  m_io_service_ptr       = std::make_shared<boost::asio::io_service>();
  m_async_udp_client_ptr = std::make_shared<sick::communication::AsyncUDPClient>(
    boost::bind(&SickSafetyscanners::processUDPPacket, this, _1),
    boost::ref(*m_io_service_ptr),
    settings.getHostUdpPort());
  m_packet_merger_ptr = std::make_shared<sick::data_processing::UDPPacketMerger>();
  ROS_INFO("Started SickSafetyscanners");
}

SickSafetyscanners::~SickSafetyscanners()
{
  m_udp_client_thread_ptr.reset();
}

bool SickSafetyscanners::run()
{
  m_udp_client_thread_ptr.reset(
    new boost::thread(boost::bind(&SickSafetyscanners::UDPClientThread, this)));

  m_async_udp_client_ptr->run_service();
  return true;
}

bool SickSafetyscanners::UDPClientThread()
{
  ROS_INFO("Enter io thread");
  m_io_work_ptr = std::make_shared<boost::asio::io_service::work>(boost::ref(*m_io_service_ptr));
  m_io_service_ptr->run();
  ROS_INFO("Exit io thread");
  return true;
}


void SickSafetyscanners::processTCPPacket(const sick::datastructure::PacketBuffer& buffer)
{
  // Not needed for current functionality, inplace for possible future developments
}

void SickSafetyscanners::changeSensorSettings(const datastructure::CommSettings& settings)
{
  startTCPConnection(settings);

  changeCommSettingsinColaSession(settings);

  stopTCPConnection();
}

void SickSafetyscanners::requestTypeCode(const datastructure::CommSettings& settings,
                                         sick::datastructure::TypeCode& type_code)
{
  startTCPConnection(settings);

  requestTypeCodeinColaSession(type_code);

  stopTCPConnection();
}

void SickSafetyscanners::startTCPConnection(const sick::datastructure::CommSettings& settings)
{
  std::shared_ptr<sick::communication::AsyncTCPClient> async_tcp_client =
    std::make_shared<sick::communication::AsyncTCPClient>(
      boost::bind(&SickSafetyscanners::processTCPPacket, this, _1),
      boost::ref(*m_io_service_ptr),
      settings.getSensorIp(),
      settings.getSensorTcpPort());
  async_tcp_client->do_connect();
  m_session_ptr = std::make_shared<sick::cola2::Cola2Session>(async_tcp_client);
}

void SickSafetyscanners::changeCommSettingsinColaSession(
  const datastructure::CommSettings& settings)
{
  m_session_ptr->open();
  sick::cola2::Cola2Session::CommandPtr command_ptr =
    std::make_shared<sick::cola2::ChangeCommSettingsCommand>(boost::ref(*m_session_ptr), settings);
  m_session_ptr->executeCommand(command_ptr);

  sick::datastructure::FieldData field_data;
  command_ptr = std::make_shared<sick::cola2::FieldHeaderVariableCommand>(
    boost::ref(*m_session_ptr), field_data, 1);
  m_session_ptr->executeCommand(command_ptr);

  command_ptr = std::make_shared<sick::cola2::FieldGeometryVariableCommand>(
    boost::ref(*m_session_ptr), field_data, 1);
  m_session_ptr->executeCommand(command_ptr);

  command_ptr = std::make_shared<sick::cola2::MonitoringCaseTableHeaderVariableCommand>(
    boost::ref(*m_session_ptr), field_data);
  m_session_ptr->executeCommand(command_ptr);

  command_ptr = std::make_shared<sick::cola2::DeviceNameVariableCommand>(boost::ref(*m_session_ptr),
                                                                         m_device_name);
  m_session_ptr->executeCommand(command_ptr);

  ROS_INFO("Device name: %s", m_device_name.c_str());

  m_session_ptr->close();
}

void SickSafetyscanners::requestTypeCodeinColaSession(sick::datastructure::TypeCode& type_code)
{
  m_session_ptr->open();
  sick::cola2::Cola2Session::CommandPtr command_ptr =
    std::make_shared<sick::cola2::TypeCodeVariableCommand>(boost::ref(*m_session_ptr), type_code);
  m_session_ptr->executeCommand(command_ptr);

  m_session_ptr->close();
}

void SickSafetyscanners::stopTCPConnection()
{
  m_session_ptr.reset();
}


void SickSafetyscanners::processUDPPacket(const sick::datastructure::PacketBuffer& buffer)
{
  if (m_packet_merger_ptr->addUDPPacket(buffer))
  {
    sick::datastructure::PacketBuffer deployedBuffer =
      m_packet_merger_ptr->getDeployedPacketBuffer();
    sick::datastructure::Data data;
    sick::data_processing::ParseData data_parser;
    data_parser.parseUDPSequence(deployedBuffer, data);

    m_newPacketReceivedCallbackFunction(data);
  }
}

} // namespace sick
