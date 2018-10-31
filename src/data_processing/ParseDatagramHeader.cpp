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
 * \file ParseDatagramHeader.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/data_processing/ParseDatagramHeader.h>

namespace sick {
namespace data_processing {

ParseDatagramHeader::ParseDatagramHeader()
{
  m_reader_ptr = std::make_shared<sick::data_processing::ReadWriteHelper>();
}

bool ParseDatagramHeader::parseUDPSequence(const datastructure::PacketBuffer& buffer,
                                           datastructure::DatagramHeader& header) const
{
  const uint8_t* data_ptr(buffer.getBuffer().data());
  setDataInHeader(data_ptr, header);
  return true;
}

void ParseDatagramHeader::setDataInHeader(const uint8_t*& data_ptr,
                                          datastructure::DatagramHeader& header) const
{
  setDatagramMarkerInHeader(data_ptr, header);
  setProtocolInHeader(data_ptr, header);
  setMajorVersionInHeader(data_ptr, header);
  setMinorVersionInHeader(data_ptr, header);
  setTotalLengthInHeader(data_ptr, header);
  setIdentificationInHeader(data_ptr, header);
  setFragmentOffsetInHeader(data_ptr, header);
}

void ParseDatagramHeader::setDatagramMarkerInHeader(const uint8_t*& data_ptr,
                                                    datastructure::DatagramHeader& header) const
{
  header.setDatagramMarker(m_reader_ptr->readuint32_tBigEndian(data_ptr, 0));
}

void ParseDatagramHeader::setProtocolInHeader(const uint8_t*& data_ptr,
                                              datastructure::DatagramHeader& header) const
{
  header.setProtocol(m_reader_ptr->readuint16_tBigEndian(data_ptr, 4));
}

void ParseDatagramHeader::setMajorVersionInHeader(const uint8_t*& data_ptr,
                                                  datastructure::DatagramHeader& header) const
{
  header.setMajorVersion(m_reader_ptr->readuint8_tLittleEndian(data_ptr, 6));
}

void ParseDatagramHeader::setMinorVersionInHeader(const uint8_t*& data_ptr,
                                                  datastructure::DatagramHeader& header) const
{
  header.setMinorVersion(m_reader_ptr->readuint8_tLittleEndian(data_ptr, 7));
}

void ParseDatagramHeader::setTotalLengthInHeader(const uint8_t*& data_ptr,
                                                 datastructure::DatagramHeader& header) const
{
  header.setTotalLength(m_reader_ptr->readuint32_tLittleEndian(data_ptr, 8));
}

void ParseDatagramHeader::setIdentificationInHeader(const uint8_t*& data_ptr,
                                                    datastructure::DatagramHeader& header) const
{
  header.setIdentification(m_reader_ptr->readuint32_tLittleEndian(data_ptr, 12));
}

void ParseDatagramHeader::setFragmentOffsetInHeader(const uint8_t*& data_ptr,
                                                    datastructure::DatagramHeader& header) const
{
  header.setFragmentOffset(m_reader_ptr->readuint32_tLittleEndian(data_ptr, 16));
}

} // namespace data_processing
} // namespace sick
