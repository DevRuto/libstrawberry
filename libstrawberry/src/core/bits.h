/*****************************************************************************
**                                                                          **
**  This file is part of libstrawberry.                                     **
**                                                                          **
**  libstrawberry is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by    **
**  the Free Software Foundation, either version 3 of the License, or       **
**  (at your option) any later version.                                     **
**                                                                          **
**  libstrawberry is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **
**  GNU General Public License for more details.                            **
**                                                                          **
**  You should have received a copy of the GNU General Public License       **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                          **
******************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CORE_BITS_H
#define __SB_CORE_BITS_H


#include <stdint.h>
#include "platform.h"


#define SB_BIT_1							1
#define SB_BIT_2							2
#define SB_BIT_3							4
#define SB_BIT_4							8
#define SB_BIT_5							16
#define SB_BIT_6							32
#define SB_BIT_7							64
#define SB_BIT_8							128
#define SB_BIT_9							256
#define SB_BIT_10							512
#define SB_BIT_11							1024
#define SB_BIT_12							2048
#define SB_BIT_13							4096
#define SB_BIT_14							8192
#define SB_BIT_15							16384
#define SB_BIT_16							32768


#define SB_OR(x, y)							((x) | (y))
#define SB_XOR(x, y)						((x) ^ (y))
#define SB_AND(x, y)						((x) & (y))
#define SB_NOT(x)							(~(x))

#define SB_NOR(x, y)						(SB_NOT( SB_OR(x, y)))
#define SB_NXOR(x, y)						(SB_NOT(SB_XOR(x, y)))
#define SB_NAND(x, y)						(SB_NOT(SB_AND(x, y)))


#define SB_FLAG(x, y)						(SB_AND(x, y) == (y))


#define SB_ROTL8(x, y)						(((x) << (y)) | ((x) >> (-(y) &  7)))
#define SB_ROTR8(x, y)						(((x) >> (y)) | ((x) << (-(y) &  7)))

#define SB_ROTL16(x, y)						(((x) << (y)) | ((x) >> (-(y) & 15)))
#define SB_ROTR16(x, y)						(((x) >> (y)) | ((x) << (-(y) & 15)))

#define SB_ROTL32(x, y)						(((x) << (y)) | ((x) >> (-(y) & 31)))
#define SB_ROTR32(x, y)						(((x) >> (y)) | ((x) << (-(y) & 31)))

#define SB_ROTL64(x, y)						(((x) << (y)) | ((x) >> (-(y) & 63)))
#define SB_ROTR64(x, y)						(((x) >> (y)) | ((x) << (-(y) & 63)))


#define SB_8M16(x, y)						(((uint16_t)(x) <<  8) | (uint16_t)(y))
#define SB_8M32(w, x, y, z)					(((uint32_t)(w) << 24) | ((uint32_t)(x) << 16) | ((uint32_t)(y) << 8) | (uint32_t)(z))
#define SB_8M64(a, b, c, d, w, x, y, z) \
											(((uint64_t)(a) << 56) | ((uint64_t)(b) << 48) | ((uint64_t)(c) << 40) | ((uint64_t)(d) << 32) | SB_8M32(w, x, y, z))
#define SB_16M32(x, y)						(((uint32_t)(x) << 16) | (uint32_t)(y))
#define SB_32M64(x, y)						(((uint64_t)(x) << 32) | (uint64_t)(y))

#define SB_8BM32(x)							SB_8M32((x)[0], (x)[1], (x)[2], (x)[3])


#define SB_4FLIP2(x)						(((((x) << 2) & 0b1100    ) | (((x) >> 2) & 0b0011    )))
#define SB_8FLIP4(x)						(((((x) << 4) & 0b11110000) | (((x) >> 4) & 0b00001111)))
#define SB_8FLIP2(x)						(SB_4FLIP2((x) >> 4) | SB_4FLIP2(x))


#define SB_LFSR(x,y)						(((x) & 1) ? ((((x) ^ 0x80000055) >> (y)) | 0x80000000) : ((x) >> (y)))


#define SB_IBO_SWAP16(x)					(SB_ROTL16((x), 8))
#define SB_IBO_SWAP32(x)					((SB_ROTL32((x), 8) & 0x00FF00FF) | (SB_ROTR32((x), 8) & 0xFF00FF00))
#define SB_IBO_SWAP64(x)					((SB_ROTL64((x), 8) & 0x00FF00FF00FF00FF) | (SB_ROTR64((x), 8) & 0xFF00FF00FF00FF00))


#define SB_HI4(x8)							(((x8) >> 4) & 7)
#define SB_LO4(x8)							((x8) & 7)
#define SB_HI5(x)							(x)
#define SB_HI8(x16)							(((x16) >> 8) & 0xFF)
#define SB_LO8(x16)							((x16) & 0xFF)
#define SB_HI16(x32)						(((x32) >> 16) & 0xFFFF)
#define SB_LO16(x32)						((x32) & 0xFFFF)
#define SB_HI32(x64)						(((x64) >> 32) & 0xFFFFFFFF)
#define SB_LO32(x64)						((x64) & 0xFFFFFFFF)


#if (SB_ENDIANNESS == SB_ENDIANNESS_BIG)
#	define SB_LE16(x)						SB_IBO_SWAP16(x)
#	define SB_BE16(x)						(x)
#	define SB_LE32(x)						SB_IBO_SWAP32(x)
#	define SB_BE32(x)						(x)
#	define SB_LE64(x)						SB_IBO_SWAP64(x)
#	define SB_BE64(x)						(x)
#else
#	define SB_LE16(x)						(x)
#	define SB_BE16(x)						SB_IBO_SWAP16(x)
#	define SB_LE32(x)						(x)
#	define SB_BE32(x)						SB_IBO_SWAP32(x)
#	define SB_LE64(x)						(x)
#	define SB_BE64(x)						SB_IBO_SWAP64(x)
#endif


#endif