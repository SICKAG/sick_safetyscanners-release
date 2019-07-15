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
 * \file ParseDataHeader.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/data_processing/ParseDataHeader.h>

namespace sick {
namespace data_processing {

ParseDataHeader::ParseDataHeader() {}

datastructure::DataHeader
ParseDataHeader::parseUDPSequence(const datastructure::PacketBuffer& buffer,
                                  datastructure::Data& data) const
{
  // Keep our own copy of the shared_ptr to keep the iterators valid
  const std::shared_ptr<std::vector<uint8_t> const> vecPtr = buffer.getBuffer();
  std::vector<uint8_t>::const_iterator data_ptr            = vecPtr->begin();
  datastructure::DataHeader data_header;
  setDataInDataHeader(data_ptr, data_header);
  return data_header;
}

void ParseDataHeader::setDataInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                          datastructure::DataHeader& data_header) const
{
  setVersionInDataHeader(data_ptr, data_header);
  setScanHeaderInDataHeader(data_ptr, data_header);
  setDataBlocksInDataHeader(data_ptr, data_header);
}


void ParseDataHeader::setVersionInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                             datastructure::DataHeader& data_header) const
{
  setVersionIndicatorInDataHeader(data_ptr, data_header);
  setMajorVersionInDataHeader(data_ptr, data_header);
  setMinorVersionInDataHeader(data_ptr, data_header);
  setVersionReleaseInDataHeader(data_ptr, data_header);
  setSerialNumberOfDeviceInDataHeader(data_ptr, data_header);
  setSerialNumberOfSystemPlugInDataHeader(data_ptr, data_header);
}

void ParseDataHeader::setScanHeaderInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                datastructure::DataHeader& data_header) const
{
  setChannelNumberInDataHeader(data_ptr, data_header);
  setSequenceNumberInDataHeader(data_ptr, data_header);
  setScanNumberInDataHeader(data_ptr, data_header);
  setTimestampDateInDataHeader(data_ptr, data_header);
  setTimestampTimeInDataHeader(data_ptr, data_header);
}

void ParseDataHeader::setDataBlocksInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                datastructure::DataHeader& data_header) const
{
  setGeneralSystemStateBlockOffsetInDataHeader(data_ptr, data_header);
  setGeneralSystemStateBlockSizeInDataHeader(data_ptr, data_header);
  setDerivedValuesBlockOffsetInDataHeader(data_ptr, data_header);
  setDerivedValuesBlockSizeInDataHeader(data_ptr, data_header);
  setMeasurementDataBlockOffsetInDataHeader(data_ptr, data_header);
  setMeasurementDataBlockSizeInDataHeader(data_ptr, data_header);
  setIntrusionDataBlockOffsetInDataHeader(data_ptr, data_header);
  setIntrusionDataBlockSizeInDataHeader(data_ptr, data_header);
  setApplicationDataBlockOffsetInDataHeader(data_ptr, data_header);
  setApplicationDataBlockSizeInDataHeader(data_ptr, data_header);
}

void ParseDataHeader::setVersionIndicatorInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                      datastructure::DataHeader& data_header) const
{
  data_header.setVersionIndicator(ReadWriteHelper::readuint8_tLittleEndian(data_ptr + 0));
}

void ParseDataHeader::setMajorVersionInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                  datastructure::DataHeader& data_header) const
{
  data_header.setVersionMajorVersion(ReadWriteHelper::readuint8_tLittleEndian(data_ptr + 1));
}

void ParseDataHeader::setMinorVersionInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                  datastructure::DataHeader& data_header) const
{
  data_header.setVersionMinorVersion(ReadWriteHelper::readuint8_tLittleEndian(data_ptr + 2));
}

void ParseDataHeader::setVersionReleaseInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                    datastructure::DataHeader& data_header) const
{
  data_header.setVersionRelease(ReadWriteHelper::readuint8_tLittleEndian(data_ptr + 3));
}

void ParseDataHeader::setSerialNumberOfDeviceInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setSerialNumberOfDevice(ReadWriteHelper::readuint32_tLittleEndian(data_ptr + 4));
}

void ParseDataHeader::setSerialNumberOfSystemPlugInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setSerialNumberOfSystemPlug(ReadWriteHelper::readuint32_tLittleEndian(data_ptr + 8));
}

void ParseDataHeader::setChannelNumberInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                   datastructure::DataHeader& data_header) const
{
  data_header.setChannelNumber(ReadWriteHelper::readuint8_tLittleEndian(data_ptr + 12));
}

void ParseDataHeader::setSequenceNumberInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                    datastructure::DataHeader& data_header) const
{
  data_header.setSequenceNumber(ReadWriteHelper::readuint32_tLittleEndian(data_ptr + 16));
}

void ParseDataHeader::setScanNumberInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                datastructure::DataHeader& data_header) const
{
  data_header.setScanNumber(ReadWriteHelper::readuint32_tLittleEndian(data_ptr + 20));
}

void ParseDataHeader::setTimestampDateInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                   datastructure::DataHeader& data_header) const
{
  data_header.setTimestampDate(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 24));
}

void ParseDataHeader::setTimestampTimeInDataHeader(std::vector<uint8_t>::const_iterator data_ptr,
                                                   datastructure::DataHeader& data_header) const
{
  data_header.setTimestampTime(ReadWriteHelper::readuint32_tLittleEndian(data_ptr + 28));
}

void ParseDataHeader::setGeneralSystemStateBlockOffsetInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setGeneralSystemStateBlockOffset(
    ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 32));
}

void ParseDataHeader::setGeneralSystemStateBlockSizeInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setGeneralSystemStateBlockSize(
    ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 34));
}

void ParseDataHeader::setDerivedValuesBlockOffsetInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setDerivedValuesBlockOffset(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 36));
}

void ParseDataHeader::setDerivedValuesBlockSizeInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setDerivedValuesBlockSize(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 38));
}

void ParseDataHeader::setMeasurementDataBlockOffsetInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setMeasurementDataBlockOffset(
    ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 40));
}

void ParseDataHeader::setMeasurementDataBlockSizeInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setMeasurementDataBlockSize(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 42));
}

void ParseDataHeader::setIntrusionDataBlockOffsetInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setIntrusionDataBlockOffset(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 44));
}

void ParseDataHeader::setIntrusionDataBlockSizeInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setIntrusionDataBlockSize(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 46));
}

void ParseDataHeader::setApplicationDataBlockOffsetInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setApplicationDataBlockOffset(
    ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 48));
}

void ParseDataHeader::setApplicationDataBlockSizeInDataHeader(
  std::vector<uint8_t>::const_iterator data_ptr, datastructure::DataHeader& data_header) const
{
  data_header.setApplicationDataBlockSize(ReadWriteHelper::readuint16_tLittleEndian(data_ptr + 50));
}

} // namespace data_processing
} // namespace sick
