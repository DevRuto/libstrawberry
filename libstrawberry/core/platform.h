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
#define SB_PLATFORM_ID_IOS					0x00BA771E

#define SB_COMPILER_ID_GCC					0x600D
#define SB_COMPILER_ID_MSC					0xBAAD
#define SB_COMPILER_ID_INTEL				0xB0B0
#define SB_COMPILER_ID_LLVM					0xBABA

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


#ifndef SB_COMPILER
#	if defined(_MSC_VER)
#		define SB_COMPILER					SB_COMPILER_ID_MSC
#		define SB_COMPILER_STRING			"MSC"
#		define SB_COMPILER_STRING_FULL		"Microsoft Visual C++"
#	elif defined(__GNUC__)
#		define SB_COMPILER					SB_COMPILER_ID_GCC
#		define SB_COMPILER_STRING			"GCC"
#		define SB_COMPILER_STRING_FULL		"GNU Compiler Collection"
#	elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#		define SB_COMPILER					SB_COMPILER_ID_INTEL
#		define SB_COMPILER_STRING			"ICL"
#		define SB_COMPILER_STRING_FULL		"Intel C/C++"
#	elif defined(__llvm__)
#		define SB_COMPILER					SB_COMPILER_ID_LLVM
#		define SB_COMPILER_STRING			"LLVM"
#		define SB_COMPILER_STRING_FULL		"Low Level Virtual Machine"
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
#elif (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	define _WIN32_WINNT						0x0501
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <windows.h>
//#elif (SB_PLATFORM == SB_PLATFORM_ID_ANDROID)
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
#	define SB_CHANNEL_STR					"Debug"
#elif defined(_RELEASE) || defined(RELEASE)
#	define SB_DEBUG							0
#	define SB_CHANNEL_STR					"Release"
#else
#	define SB_DEBUG							0
#	define SB_CHANNEL_STR					"Unspecified"
#endif


#if defined(SB_INCLUDE_INTRINSICS) && defined(SB_INTRINSICS)
#	if (SB_COMPILER == SB_COMPILER_ID_GCC)
#		if !defined(SB_ASSUME_INTRINSICS_AVAILABLE) && defined(__has_include)
#			if __has_include(<x86intrin.h>)
#				include <x86intrin.h>
#				define SB_HAVE_INTRINSICS	1
#			else
#				define SB_HAVE_INTRINSICS	0
#			endif
#		else
#			include <x86intrin.h>
#			define SB_HAVE_INTRINSICS		1
#		endif
#	elif (SB_COMPILER == SB_COMPILER_ID_MSC)
#		if !defined(SB_ASSUME_INTRINSICS_AVAILABLE) && defined(__has_include)
#			if __has_include(<intrin.h>)
#				include <intrin.h>
#				define SB_HAVE_INTRINSICS	1
#			else
#				define SB_HAVE_INTRINSICS	0
#			endif
#		else
#			include <intrin.h>
#			define SB_HAVE_INTRINSICS		1
#		endif
#	else
#		define SB_HAVE_INTRINSICS			0
#	endif
#else
#	define SB_HAVE_INTRINSICS				0
#endif

#if SB_HAVE_INTRINSICS
#	define SB_INTRINSICS_STR				"+"
#else
#	define SB_INTRINSICS_STR				"-"
#endif


#define SB_MIN_UINT8						0
#define SB_MAX_UINT8						255U
#define SB_MIN_UINT16						0
#define SB_MAX_UINT16						65535U
#define SB_MIN_UINT32						0
#define SB_MAX_UINT32						4294967295U
#define SB_MIN_UINT64						0
#define SB_MAX_UINT64						18446744073709551615U


#include <stdint.h>

#define SB_MIN_SIZE							0
#if (SB_ARCH == 64)
#	define SB_MAX_SIZE						SB_MAX_UINT64
	typedef uint64_t sb_size_t;
	typedef int64_t sb_ssize_t;
#else
#	define SB_MAX_SIZE						SB_MAX_UINT32
	typedef uint32_t sb_size_t;
	typedef int32_t sb_ssize_t;
#endif


#define SB_FULL_PLATFORM_STRING				SB_PLATFORM_STRING" ("SB_ARCH_STRING", "SB_ENDIANNESS_STRING", "SB_COMPILER_STRING""SB_INTRINSICS_STR")"


#ifdef REPORT_PLATFORM
#	pragma message("  platform.h: "SB_FULL_PLATFORM_STRING)
#endif


#endif
