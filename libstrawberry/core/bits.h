/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CORE_BITS_H
#define __SB_CORE_BITS_H


#include <stdint.h>
#include "./platform.h"


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
#define SB_BIT_17							65536
#define SB_BIT_18							131072
#define SB_BIT_19							262144
#define SB_BIT_20							524288
#define SB_BIT_21							1048576
#define SB_BIT_22							2097152
#define SB_BIT_23							4194304
#define SB_BIT_24							8388608
#define SB_BIT_25							16777216
#define SB_BIT_26							33554432
#define SB_BIT_27							67108864
#define SB_BIT_28							134217728
#define SB_BIT_29							268435456
#define SB_BIT_30							536870912
#define SB_BIT_31							1073741824
#define SB_BIT_32							2147483648


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
#define SB_8M64(a, b, c, d, w, x, y, z)		(((uint64_t)(a) << 56) | ((uint64_t)(b) << 48) | ((uint64_t)(c) << 40) | ((uint64_t)(d) << 32) | SB_8M32(w, x, y, z))
#define SB_16M32(x, y)						(((uint32_t)(x) << 16) | (uint32_t)(y))
#define SB_32M64(x, y)						(((uint64_t)(x) << 32) | (uint64_t)(y))

#define SB_8BM32(x)							SB_8M32((x)[0], (x)[1], (x)[2], (x)[3])


#define SB_4FLIP2(x)						(((((x) << 2) & 0b1100    ) | (((x) >> 2) & 0b0011    )))
#define SB_8FLIP4(x)						(((((x) << 4) & 0b11110000) | (((x) >> 4) & 0b00001111)))
#define SB_8FLIP2(x)						(SB_4FLIP2((x) >> 4) | SB_4FLIP2(x))


#define SB_LFSR(x,y)						(((x) & 1) ? ((((x) ^ 0x80000055) >> (y)) | 0x80000000) : ((x) >> (y)))


#if ((SB_COMPILER == SB_COMPILER_ID_GCC) || (SB_COMPILER == SB_COMPILER_ID_LLVM)) && SB_HAVE_INTRINSICS
#	define SB_IBO_SWAP16(x)					__builtin_bswap16(x)
#	define SB_IBO_SWAP32(x)					__builtin_bswap32(x)
#	define SB_IBO_SWAP64(x)					__builtin_bswap64(x)
#else
#	define SB_IBO_SWAP16(x)					(					\
		(((x) & 0xFF00            ) >>  8) |					\
		(((x) & 0x00FF            ) <<  8)						\
	)

#	define SB_IBO_SWAP32(x)					(					\
		(((x) & 0xFF000000        ) >> 24) |					\
		(((x) & 0x00FF0000        ) >>  8) |					\
		(((x) & 0x0000FF00        ) <<  8) |					\
		(((x) & 0x000000FF        ) << 24)						\
	)

#	define SB_IBO_SWAP64(x)					(					\
		(((x) & 0xFF00000000000000) >> 56) |					\
		(((x) & 0x00FF000000000000) >> 40) |					\
		(((x) & 0x0000FF0000000000) >> 24) |					\
		(((x) & 0x000000FF00000000) >>  8) |					\
		(((x) & 0x00000000FF000000) <<  8) |					\
		(((x) & 0x0000000000FF0000) << 24) |					\
		(((x) & 0x000000000000FF00) << 40) |					\
		(((x) & 0x00000000000000FF) << 56)						\
	)
#endif


#define SB_HI4(x8)							(((x8) >> 4) & 7)
#define SB_LO4(x8)							((x8) & 7)
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


#define SB_VALID_KEX_BITS(x)				((((x) % 8) == 0))// && ((((x) / 8) % 8) == 0))


#endif
