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

#ifndef __SB_CORE_PLATFORM_H
#define __SB_CORE_PLATFORM_H


#define _SB_STRINGIFY_MACRO(x)				#x
#define SB_STRINGIFY_MACRO(x)				_SB_STRINGIFY_MACRO(x)


#define SB_PLATFORM_ID_UNKNOWN				0x00000000
#define SB_PLATFORM_ID_WINDOWS				0xDEFEC8ED
#define SB_PLATFORM_ID_LINUX				0x00BAC001
#define SB_PLATFORM_ID_LINUX_ARM			0x00BAF00D
#define SB_PLATFORM_ID_ANDROID				0x0A0D001D
#define SB_PLATFORM_ID_MAC					0xBADA771E

#define SB_ARCH_X86							32
#define SB_ARCH_X64							64

#define SB_ENDIANNESS_LITTLE				0
#define SB_ENDIANNESS_BIG					1


#ifndef SB_PLATFORM
#	if defined(__gnu_linux__) || defined(__linux__) || defined(linux)
#		if defined(__ANDROID__) || defined(__ANDROID_API__)
#			define SB_PLATFORM				SB_PLATFORM_ID_ANDROID
#			define SB_PLATFORM_STRING		"Android"
#		elif defined(__ARMCC_VERSION) || defined(__CC_ARM)
#			define SB_PLATFORM				SB_PLATFORM_ID_LINUX_ARM
#			define SB_PLATFORM_STRING		"Linux (ARM)"
#		else
#			define SB_PLATFORM				SB_PLATFORM_ID_LINUX
#			define SB_PLATFORM_STRING		"Linux"
#		endif
#	elif defined(_WIN32)
#		define SB_PLATFORM					SB_PLATFORM_ID_WINDOWS
#		define SB_PLATFORM_STRING			"Windows"
#	elif (defined(__APPLE__) && defined(__MACH__))
#		define SB_PLATFORM					SB_PLATFORM_ID_MAC
#		define SB_PLATFORM_STRING			"Mac"
#	else
#		define SB_PLATFORM					SB_PLATFORM_ID_UNKNOWN
#		define SB_PLATFORM_STRING			"Unknown"
#	endif
#endif


#ifndef SB_ARCH
#	if defined(_WIN64) || defined(__x86_64) || defined(__x86_64__) || defined(__ppc64__)
#		define SB_ARCH						SB_ARCH_X64
#		define SB_ARCH_STRING				"x64"
#	else
#		define SB_ARCH						SB_ARCH_X86
#		define SB_ARCH_STRING				"x86"
#	endif
#endif


#if (SB_PLATFORM == SB_PLATFORM_ID_LINUX)
	// todo
#elif (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX	// FIX the stupid LOWERCASEEEEEEEEEEE min/max
#	include <windows.h>
#elif (SB_PLATFORM == SB_PLATFORM_ID_ANDROID)
	// todo
#else
#	ifndef IGNORE_UNSUPPORTED_PLATFORM
#		pragma message("  Platform: "SB_PLATFORM_STRING)
#		pragma message("! Refusing to compile. Override with -DIGNORE_UNSUPPORTED_PLATFORM.")
#		error fatal
#	endif
#endif


#ifndef SB_ENDIANNESS
#	if defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__) || ((SB_PLATFORM == SB_PLATFORM_ID_WINDOWS && REG_DWORD == REG_DWORD_BIG_ENDIAN) || (SB_PLATFORM != SB_PLATFORM_ID_WINDOWS && ((__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)/* || (__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__)*/)))
#		define SB_ENDIANNESS				SB_ENDIANNESS_BIG
#		define SB_ENDIANNESS_STRING			"big-endian"
#	else
#		define SB_ENDIANNESS				SB_ENDIANNESS_LITTLE
#		define SB_ENDIANNESS_STRING			"little-endian"
#	endif
#endif


#if defined(_DEBUG) || defined(DEBUG)
#	define SB_DEBUG							1
#else
#	define SB_DEBUG							0
#endif


#define SB_FULL_PLATFORM_STRING				SB_PLATFORM_STRING" ("SB_ARCH_STRING", "SB_ENDIANNESS_STRING", dbg="SB_STRINGIFY_MACRO(SB_DEBUG)")"

#ifndef SB_DIAG_FILE_START
#	define SB_DIAG_FILE_START				85
#endif
#define SB_DIAG_FUNC						__func__
#define SB_DIAG_LINE						__LINE__
#define SB_DIAG_FILE						(__FILE__ + SB_DIAG_FILE_START)


#ifndef DONT_REPORT_PLATFORM
#pragma message("  platform.h: "SB_FULL_PLATFORM_STRING)
#endif


#define SB_MIN_UINT8                0
#define SB_MAX_UINT8                255U
#define SB_MIN_UINT16               0
#define SB_MAX_UINT16               65535U
#define SB_MIN_UINT32               0
#define SB_MAX_UINT32               4294967295U
#define SB_MIN_UINT64               0
#define SB_MAX_UINT64               18446744073709551615U


#include <stdint.h>

#if (SB_ARCH == 64)
#	define SB_MAX_SIZE						SB_MAX_UINT64
	typedef uint64_t sb_size_t;
	typedef int64_t sb_ssize_t;
#else
#	define SB_MAX_SIZE						SB_MAX_UINT32
	typedef uint32_t sb_size_t;
	typedef int32_t sb_ssize_t;
#endif


#endif