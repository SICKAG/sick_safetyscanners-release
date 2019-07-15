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
 * \file ReadWriteHelper.hpp
 *
 * \author  Lennart Puck <puck@fzi.de>
 * \date    2018-09-24
 */
//----------------------------------------------------------------------

#ifndef SICK_SAFETYSCANNERS_DATA_PROCESSING_READWRITEHELPER_HPP
#define SICK_SAFETYSCANNERS_DATA_PROCESSING_READWRITEHELPER_HPP

#include <stdint.h>

namespace sick {
namespace ReadWriteHelper {

/*!
 * \brief Helper Functions read and write data at a certain place in a buffer.
 */

/*!
 * \brief Writes an unsigned 8-bit integer to a buffer at offset.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.
 */
inline void writeuint8_t(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  *(it + 0) = v;
}

/*!
 * \brief Writes an unsigned 8-bit integer to a buffer at offset in big endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint8_tBigEndian(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  writeuint8_t(it, v);
}

/*!
 * \brief Writes an unsigned 8-bit integer to a buffer at offset in little endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint8_tLittleEndian(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  writeuint8_t(it, v);
}

/*!
 * \brief Writes a signed 8-bit integer to a buffer at offset.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeint8_t(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  writeuint8_t(it, v);
}

/*!
 * \brief Writes a signed 8-bit integer to a buffer at offset in big endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeint8_tBigEndian(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  writeint8_t(it, v);
}

/*!
 * \brief Writes a signed 8-bit integer to a buffer at offset in little endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeint8_tLittleEndian(std::vector<uint8_t>::iterator it, const uint8_t v)
{
  writeint8_t(it, v);
}

/*!
 * \brief Writes an unsigned 16-bit integer to a buffer at offset in big endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint16_tBigEndian(std::vector<uint8_t>::iterator it, const uint16_t v)
{
  *(it + 0) = (v & 0xff00) >> 8;
  *(it + 1) = v & 0xff;
}

/*!
 * \brief Writes an unsigned 16-bit integer to a buffer at offset in little endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint16_tLittleEndian(std::vector<uint8_t>::iterator it, const uint16_t v)
{
  *(it + 0) = v & 0xff;
  *(it + 1) = (v & 0xff00) >> 8;
}


/*!
 * \brief Writes an unsigned 32-bit integer to a buffer at offset in big endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint32_tBigEndian(std::vector<uint8_t>::iterator it, const uint32_t v)
{
  *(it + 0) = (v & 0xff000000) >> 24;
  *(it + 1) = (v & 0xff0000) >> 16;
  *(it + 2) = (v & 0xff00) >> 8;
  *(it + 3) = v & 0xff;
}

/*!
 * \brief Writes an unsigned 32-bit integer to a buffer at offset in little endian encoding.
 *
 * \param buf The buffer to write to.
 * \param v Value which will be written.

 */
inline void writeuint32_tLittleEndian(std::vector<uint8_t>::iterator it, const uint32_t v)
{
  *(it + 3) = (v & 0xff000000) >> 24;
  *(it + 2) = (v & 0xff0000) >> 16;
  *(it + 1) = (v & 0xff00) >> 8;
  *(it + 0) = v & 0xff;
}

/*!
 * \brief Read an unsigned 8-bit integer at offset.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint8_t readuint8_t(std::vector<uint8_t>::const_iterator it)
{
  return *(it + 0);
}

/*!
 * \brief Read an unsigned 8-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint8_t readuint8_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint8_t(it);
}

/*!
 * \brief Read an unsigned 8-bit integer at offset in big little encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint8_t readuint8_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint8_t(it);
}

/*!
 * \brief Read a signed 8-bit integer at offset.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int8_t readint8_t(std::vector<uint8_t>::const_iterator it)
{
  return readuint8_t(it);
}

/*!
 * \brief Read a signed 8-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int8_t readint8_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return readint8_t(it);
}

/*!
 * \brief Read a signed 8-bit integer at offset in little endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int8_t readint8_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return readint8_t(it);
}

/*!
 * \brief Read an unsigned 16-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint16_t readuint16_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return (*(it + 0) << 8) + *(it + 1);
}

/*!
 * \brief Read an unsigned 16-bit integer at offset in little endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint16_t readuint16_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return (*(it + 1) << 8) + *(it + 0);
}

/*!
 * \brief Read a signed 16-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int16_t readint16_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint16_tBigEndian(it);
}

/*!
 * \brief Read a signed 16-bit integer at offset in little endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int16_t readint16_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint16_tLittleEndian(it);
}

/*!
 * \brief Read an unsigned 32-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint32_t readuint32_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return (*(it + 0) << 24) + (*(it + 1) << 16) + (*(it + 2) << 8) + *(it + 3);
}

/*!
 * \brief Read an unsigned 32-bit integer at offset in little endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline uint32_t readuint32_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return (*(it + 3) << 24) + (*(it + 2) << 16) + (*(it + 1) << 8) + *(it + 0);
}

/*!
 * \brief Read an unsigned 32-bit integer at offset in big endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int32_t readint32_tBigEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint32_tBigEndian(it);
}


/*!
 * \brief Read an unsigned 32-bit integer at offset in little endian encoding.
 *
 * \param buf Buffer to read from.
 * \param offset Position of integer.
 *
 * \returns The value of the read integer.
 */
inline int32_t readint32_tLittleEndian(std::vector<uint8_t>::const_iterator it)
{
  return readuint32_tLittleEndian(it);
}

} // namespace ReadWriteHelper
} // namespace sick

#endif // SICK_SAFETYSCANNERS_DATA_PROCESSING_READWRITEHELPER_HPP
