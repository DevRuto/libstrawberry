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

#define __FILE_LOCAL__						"crypto/keygen.c"

#include "./keygen.h"

#include "../core/error.h"
#include "../core/bits.h"
#include "../core/memory.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-10");


sb_bool_t sb_crypto_keygen(void *out, sb_size_t outsize, void *in, sb_size_t insize) {
	sb_error_reset();

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!outsize) {
		sb_error_set_ex(SB_ERROR_PARAM_INVALID, 1);
		return sb_false;
	}

	if (!in) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	if (!insize) {
		sb_error_set_ex(SB_ERROR_PARAM_INVALID, 2);
		return sb_false;
	}

	if (insize < outsize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return sb_false;
	}


	sb_memset(out, (SB_BIT_8 | SB_BIT_6 | SB_BIT_4 | SB_BIT_2), outsize);


	sb_bool_t m0 = sb_false, m1 = sb_false;
	sb_size_t o, i, m = 0;
	uint8_t *out8 = out, *in8 = in, mask = in8[m];
	for (i = insize, o = outsize; i--;) {
		if ((i % 3) == 0) {
			m0 = ((in8[i] % o) == 0);
		}
		m1 = SB_FLAG(mask, SB_BIT_6);
		mask >>= 1;
		if (!mask) {
			mask = in8[++m];
		}
		if (m0) {
			out8[--o] ^= (in8[i] ^ SB_ROTL8(mask, (m1 ? 3 : 5)));
		} else {
			out8[--o] ^= ~(in8[i] + SB_ROTL8(mask, (m1 ? 2 : 4)));
		}
		if (!o) {
			o = outsize;
		}
	}


	return sb_true;
}
