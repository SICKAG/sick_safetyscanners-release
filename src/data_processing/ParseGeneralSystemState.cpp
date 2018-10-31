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
 * \file ParseGeneralSystemState.cpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#include <sick_safetyscanners/data_processing/ParseGeneralSystemState.h>

namespace sick {
namespace data_processing {

ParseGeneralSystemState::ParseGeneralSystemState()
{
  m_reader_ptr = std::make_shared<sick::data_processing::ReadWriteHelper>();
}

datastructure::GeneralSystemState
ParseGeneralSystemState::parseUDPSequence(const datastructure::PacketBuffer& buffer,
                                          datastructure::Data& data) const
{
  datastructure::GeneralSystemState general_system_state;
  if (!checkIfPreconditionsAreMet(data))
  {
    general_system_state.setIsEmpty(true);
    return general_system_state;
  }
  const uint8_t* data_ptr(buffer.getBuffer().data() +
                          data.getDataHeaderPtr()->getGeneralSystemStateBlockOffset());

  setDataInGeneralSystemState(data_ptr, general_system_state);
  return general_system_state;
}

bool ParseGeneralSystemState::checkIfPreconditionsAreMet(const datastructure::Data& data) const
{
  if (!checkIfGeneralSystemStateIsPublished(data))
  {
    return false;
  }
  if (!checkIfDataContainsNeededParsedBlocks(data))
  {
    return false;
  }

  return true;
}

bool ParseGeneralSystemState::checkIfGeneralSystemStateIsPublished(
  const datastructure::Data& data) const
{
  if (data.getDataHeaderPtr()->getGeneralSystemStateBlockOffset() == 0 &&
      data.getDataHeaderPtr()->getGeneralSystemStateBlockSize() == 0)
  {
    return false;
  }
  return true;
}

bool ParseGeneralSystemState::checkIfDataContainsNeededParsedBlocks(
  const datastructure::Data& data) const
{
  if (data.getDataHeaderPtr()->isEmpty())
  {
    return false;
  }
  return true;
}


void ParseGeneralSystemState::setDataInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  setStatusBitsInGeneralSystemState(data_ptr, general_system_state);
  setSafeCutOffPathInGeneralSystemState(data_ptr, general_system_state);
  setNonSafeCutOffPathInGeneralSystemState(data_ptr, general_system_state);
  setResetRequiredCutOffPathInGeneralSystemState(data_ptr, general_system_state);
  setCurrentMonitoringCasesInGeneralSystemState(data_ptr, general_system_state);
  setErrorsInGeneralSystemState(data_ptr, general_system_state);
}

void ParseGeneralSystemState::setStatusBitsInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  uint8_t byte = m_reader_ptr->readuint8_tLittleEndian(data_ptr, 0);

  general_system_state.setRunModeActive(static_cast<bool>(byte & (0x01 << 0)));
  general_system_state.setStandbyModeActive(static_cast<bool>(byte & (0x01 << 1)));
  general_system_state.setContaminationWarning(static_cast<bool>(byte & (0x01 << 2)));
  general_system_state.setContaminationError(static_cast<bool>(byte & (0x01 << 3)));
  general_system_state.setReferenceContourStatus(static_cast<bool>(byte & (0x01 << 4)));
  general_system_state.setManipulationStatus(static_cast<bool>(byte & (0x01 << 5)));
  // bit 6 and 7 reserved
}

void ParseGeneralSystemState::setSafeCutOffPathInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  std::vector<bool> safe_cut_off_path;

  for (uint8_t i = 0; i < 3; i++)
  {
    uint8_t byte = m_reader_ptr->readuint8_tLittleEndian(data_ptr, 1 + i);

    for (uint8_t j = 0; j < 8; j++)
    {
      // as long as there are only 20 instead of 24 cut off paths
      if (i == 2 && j > 3)
      {
        break;
      }
      safe_cut_off_path.push_back(static_cast<bool>(byte & (0x01 << j)));
    }
  }
  general_system_state.setSafeCutOffPathvector(safe_cut_off_path);
}

void ParseGeneralSystemState::setNonSafeCutOffPathInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  std::vector<bool> non_safe_cut_off_path;

  for (uint8_t i = 0; i < 3; i++)
  {
    uint8_t byte = m_reader_ptr->readuint8_tLittleEndian(data_ptr, 4 + i);

    for (uint8_t j = 0; j < 8; j++)
    {
      // as long as there are only 20 instead of 24 cut off paths
      if (i == 2 && j > 3)
      {
        break;
      }
      non_safe_cut_off_path.push_back(static_cast<bool>(byte & (0x01 << j)));
    }
  }
  general_system_state.setNonSafeCutOffPathVector(non_safe_cut_off_path);
}

void ParseGeneralSystemState::setResetRequiredCutOffPathInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  std::vector<bool> reset_required_cutoff_path;

  for (uint8_t i = 0; i < 3; i++)
  {
    uint8_t byte = m_reader_ptr->readuint8_tLittleEndian(data_ptr, 7 + i);

    for (uint8_t j = 0; j < 8; j++)
    {
      // as long as there are only 20 instead of 24 cut off paths
      if (i == 2 && j > 3)
      {
        break;
      }
      reset_required_cutoff_path.push_back(static_cast<bool>(byte & (0x01 << j)));
    }
  }
  general_system_state.setResetRequiredCutOffPathVector(reset_required_cutoff_path);
}

void ParseGeneralSystemState::setCurrentMonitoringCasesInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  general_system_state.setCurrentMonitoringCaseNoTable_1(
    m_reader_ptr->readuint8_tLittleEndian(data_ptr, 10));
  general_system_state.setCurrentMonitoringCaseNoTable_2(
    m_reader_ptr->readuint8_tLittleEndian(data_ptr, 11));
  general_system_state.setCurrentMonitoringCaseNoTable_3(
    m_reader_ptr->readuint8_tLittleEndian(data_ptr, 12));
  general_system_state.setCurrentMonitoringCaseNoTable_4(
    m_reader_ptr->readuint8_tLittleEndian(data_ptr, 13));
}

void ParseGeneralSystemState::setErrorsInGeneralSystemState(
  const uint8_t*& data_ptr, datastructure::GeneralSystemState& general_system_state) const
{
  uint8_t byte = m_reader_ptr->readuint8_tLittleEndian(data_ptr, 15);
  general_system_state.setApplicationError(static_cast<bool>(byte & (0x01 << 0)));
  general_system_state.setDeviceError(static_cast<bool>(byte & (0x01 << 1)));
}

} // namespace data_processing
} // namespace sick
