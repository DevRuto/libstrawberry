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

#define __FILE_LOCAL__						"crypto/padding/iso97971-2.c"

#include "./iso97971-2.h"

#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/math.h"
#include "../../core/bits.h"

#include "./zero.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-08-12");


sb_size_t sb_crypto_pad_iso979712_size(sb_size_t blocksize, sb_size_t havesize) {
	return sb_math_round_block(blocksize, havesize);
}


sb_bool_t sb_crypto_pad_iso979712(void *out, void *in, sb_size_t blocksize, sb_size_t havesize) {
	sb_error_reset();

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!in) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	if (!blocksize) {
		sb_error_set_ex(SB_ERROR_PARAM_RANGE, 1);
		return sb_false;
	}

	if (!havesize) {
		sb_error_set_ex(SB_ERROR_PARAM_RANGE, 2);
		return sb_false;
	}

	if (sb_crypto_pad_zero(out, in, blocksize, havesize)) {
		((uint8_t*)out)[havesize] = SB_BIT_8;
		return sb_true;
	}

	return sb_false;
}


sb_size_t sb_crypto_pad_iso979712_offset(void *in, sb_size_t havesize) {
	sb_error_reset();

	if (!in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return SB_MIN_SIZE;
	}

	if (!havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return SB_MIN_SIZE;
	}

	uint8_t *pptr = in;

	sb_size_t i;
	for (i = havesize; i--;) {
		if (pptr[i]) {
			if (pptr[i] == SB_BIT_8) {
				return i;
			} else {
				return SB_MIN_SIZE;
			}
		}
	}

	return SB_MIN_SIZE;
}
