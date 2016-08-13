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

#include "../../core/identid.h"
IDENTID("pkcs7.c", "0.1", "1", "2016-07-29");

#include "pkcs7.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/math.h"


sb_size_t sb_crypto_pad_pkcs7_size(sb_size_t blocksize, sb_size_t havesize) {
	sb_size_t size = sb_math_round_block(blocksize, havesize);
	if (size == havesize) {
		size += blocksize;
	}
	return size;
}

sb_bool_t sb_crypto_pad_pkcs7(void *out, void *in, sb_size_t blocksize, sb_size_t havesize) {
	sb_error_reset();

	if (!out || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!blocksize || !havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return sb_false;
	}

	sb_size_t size = sb_crypto_pad_pkcs7_size(blocksize, havesize);
	if (size <= havesize) {
		sb_error_set(SB_ERROR_FAILSAFE);
		return sb_false;
	}

	uint8_t pad = (uint8_t)(size - havesize), pidx = pad,
#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS) // see zero.c:34
		*pptr = (((uint8_t*)out + havesize) - 1);
#else
		*pptr = ((out + havesize) - 1);
#endif
	sb_memcpy(out, in, havesize);
	for (; pidx--;) {
		*(++pptr) = pad;
	}

	return sb_true;
}

sb_size_t sb_crypto_pad_pkcs7_offset(void *in, sb_size_t havesize) {
	sb_error_reset();

	if (!in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return SB_MAX_SIZE;
	}

	if (!havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return SB_MAX_SIZE;
	}

	return (havesize - ((uint8_t*)in)[havesize - 1]);
}
