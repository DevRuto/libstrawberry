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

#ifndef __SB_CORE_STDINCL_H
#define __SB_CORE_STDINCL_H


#include <stdint.h>
#include <stddef.h>

#include "./platform.h"
#include "./identid.h"
#include "./sbapi.h"

#include "./types/bool.h"

#include "./bits.h"

#if defined(LIBSTRAWBERRY_EXPORTS) && !SB_DEBUG
#	include "./poison.h"
#endif


#define SB_VERSION_MAJOR					0
#define SB_VERSION_MINOR					1
#define SB_VERSION							((SB_VERSION_MAJOR << 16) | (SB_VERSION_MINOR << 8) | SB_DEBUG)
#define SB_VERSION_STRING					"libstrawberry "SB_STRINGIFY_MACRO(SB_VERSION_MAJOR)"."SB_STRINGIFY_MACRO(SB_VERSION_MINOR)""SB_CHANNEL_ID" ("IDENTID_CODENAME") "__DATE__" "__TIME__


#define SB_FEATURE_CORE_TYPE_DICTIONARY					SB_BIT_1
#define SB_FEATURE_CORE_CLI								SB_BIT_2
#define SB_FEATURE_CRYPTO_HASHING_MD5					SB_BIT_3
#define SB_FEATURE_CRYPTO_HASHING_RIPEMD160				SB_BIT_4
#define SB_FEATURE_CRYPTO_HASHING_SHA256				SB_BIT_5
#define SB_FEATURE_CRYPTO_HASHING_SHA512				SB_BIT_6
#define SB_FEATURE_CRYPTO_HASHING						SB_BIT_7
#define SB_FEATURE_CRYPTO_KEX_EXCHANGE_DIFFIEHELLMAN	SB_BIT_8
#define SB_FEATURE_CRYPTO_KEX_EXCHANGE					SB_BIT_9
#define SB_FEATURE_CRYPTO_OTP_ISAAC						SB_BIT_10
#define SB_FEATURE_CRYPTO_OTP							SB_BIT_11
#define SB_FEATURE_CRYPTO_PADDING_ISO979711				SB_BIT_12
#define SB_FEATURE_CRYPTO_PADDING_ISO979712				SB_BIT_13
#define SB_FEATURE_CRYPTO_PADDING_PKCS7					SB_BIT_14
#define SB_FEATURE_CRYPTO_PADDING_ZERO					SB_BIT_15
#define SB_FEATURE_CRYPTO_PADDING						SB_BIT_16
#define SB_FEATURE_CRYPTO_PRNG_ISAAC					SB_BIT_17
#define SB_FEATURE_CRYPTO_PRNG							SB_BIT_18
#define SB_FEATURE_CRYPTO_SYMMETRIC_RABBIT				SB_BIT_19
#define SB_FEATURE_CRYPTO_SYMMETRIC_RIJNDAEL			SB_BIT_20
#define SB_FEATURE_CRYPTO_SYMMETRIC_SALSA20				SB_BIT_21
#define SB_FEATURE_CRYPTO_SYMMETRIC						SB_BIT_22
#define SB_FEATURE_CRYPTO_BLOCKMODE						SB_BIT_23
#define SB_FEATURE_CRYPTO_CIPHER						SB_BIT_24
#define SB_FEATURE_CRYPTO_KEYGEN						SB_BIT_25
#define SB_FEATURE_CRYPTO_RANDOM						SB_BIT_26
#define SB_FEATURE_CRYPTO_SEEDGEN						SB_BIT_27
#define SB_FEATURE_NETWORKING							SB_BIT_28
#define SB_FEATURE_ERROR_REPORTING						SB_BIT_29


#ifdef __cplusplus
extern "C" {
#endif

	// Compile-time build information.
	SBAPI const char* sb_platform();
	SBAPI const char* sb_version();
	SBAPI const char* sb_version_full();
	SBAPI const char* sb_compiler();
	SBAPI const char* sb_compiler_full();
	SBAPI const char* sb_compile_date();
	SBAPI const char* sb_compile_time();
	SBAPI const uint64_t sb_features();


#ifdef __cplusplus
}
#endif


#endif
