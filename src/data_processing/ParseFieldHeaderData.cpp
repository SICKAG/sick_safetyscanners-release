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
 * \file ParseFieldHeaderData.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-10-16
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/data_processing/ParseFieldHeaderData.h>

#include <sick_safetyscanners/cola2/Command.h>

namespace sick {
namespace data_processing {

ParseFieldHeaderData::ParseFieldHeaderData()
{
  m_reader_ptr = std::make_shared<sick::data_processing::ReadWriteHelper>();
}


bool ParseFieldHeaderData::parseTCPSequence(const datastructure::PacketBuffer& buffer,
                                            datastructure::FieldData& field_data) const
{
  const uint8_t* data_ptr(buffer.getBuffer().data());
  setFieldType(data_ptr, field_data);
  return true;
}

void ParseFieldHeaderData::setFieldType(const uint8_t*& data_ptr,
                                        datastructure::FieldData& field_data) const
{
  uint8_t field_type = readFieldType(data_ptr);
  field_data.setIsWarningField(false);
  field_data.setIsProtectiveField(false);
  if (field_type == 4 || field_type == 14)
  {
    field_data.setIsProtectiveField(true);
  }
  else if (field_type == 5 || field_type == 15)
  {
    field_data.setIsWarningField(true);
  }
}


uint8_t ParseFieldHeaderData::readFieldType(const uint8_t*& data_ptr) const
{
  return m_reader_ptr->readuint8_t(data_ptr, 73);
}

uint16_t ParseFieldHeaderData::readSetIndex(const uint8_t*& data_ptr) const
{
  return m_reader_ptr->readuint16_tLittleEndian(data_ptr, 82);
}


} // namespace data_processing
} // namespace sick
