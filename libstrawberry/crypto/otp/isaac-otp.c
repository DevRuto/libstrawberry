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

#define __FILE_LOCAL__						"crypto/otp/isaac-otp.c"

#include "./isaac-otp.h"

#include "../../core/error.h"
#include "../../core/bits.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-10-03");


#define CREATE_OTP(name, operator)														\
sb_bool_t name(sb_crypto_otp_isaac_ctx_t *ctx, void *out, void *in, sb_size_t size) {	\
	sb_error_reset();																	\
																						\
	if (!ctx) {																			\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);											\
		return sb_false;																\
	}																					\
																						\
	if (!out) {																			\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);											\
		return sb_false;																\
	}																					\
																						\
	if (!in) {																			\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 3);											\
		return sb_false;																\
	}																					\
																						\
	if (!size) {																		\
		sb_error_set(SB_ERROR_PARAM_INVALID);											\
		return sb_false;																\
	}																					\
																						\
	if (size >= sizeof(uint32_t)) {														\
		uint32_t *out32 = out;															\
		uint32_t *in32 = in;															\
		for (;;) {																		\
			*(out32++) = (*(in32++) operator sb_crypto_prng_isaac(ctx));				\
			if ((size -= sizeof(uint32_t)) < sizeof(uint32_t)) {						\
				break;																	\
			}																			\
		}																				\
		if (size) {																		\
			uint8_t *out8 = (uint8_t*)out32;											\
			uint8_t *in8 = (uint8_t*)in32;												\
			for (; size--;) {															\
				*(out8++) = (*(in8++) operator sb_crypto_prng_isaac(ctx));				\
			}																			\
		}																				\
	} else {																			\
		uint8_t *out8 = out;															\
		uint8_t *in8 = in;																\
		for (; size--;) {																\
			*(out8++) = (*(in8++) operator sb_crypto_prng_isaac(ctx));					\
		}																				\
	}																					\
																						\
	return sb_true;																		\
}


CREATE_OTP(sb_crypto_otp_isaac_xor, ^);

CREATE_OTP(sb_crypto_otp_isaac_add, +);

CREATE_OTP(sb_crypto_otp_isaac_sub, -);
