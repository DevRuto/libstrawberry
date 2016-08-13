/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU Lesser General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU Lesser General Public License for more details.                          **
**                                                                               **
**  You should have received a copy of the GNU Lesser General Public License     **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#include "../../core/identid.h"
IDENTID("zero.c", "0.1", "1", "2016-08-10");

#include "zero.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/math.h"


sb_size_t sb_crypto_pad_zero_size(sb_size_t blocksize, sb_size_t havesize) {
	return sb_math_round_block(blocksize, havesize);
}

sb_bool_t sb_crypto_pad_zero(void *out, void *in, sb_size_t blocksize, sb_size_t havesize) {
	sb_error_reset();

	if (!out || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!blocksize || !havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return sb_false;
	}

	sb_size_t size = sb_crypto_pad_zero_size(blocksize, havesize);
	if (size < havesize) {
		sb_error_set(SB_ERROR_FAILSAFE);
		return sb_false;
	}

	sb_memcpy(out, in, havesize);
#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS) // apparently vs doesn't know how big a pointer is, but it does know how big a pointer is. thanks.
	sb_memset((uint32_t*)out + havesize, 0, size - havesize);
#else
	sb_memset(out + havesize, 0, size - havesize);
#endif

	return sb_true;
}

sb_size_t sb_crypto_pad_zero_offset(void *in, sb_size_t havesize) {
	sb_error_reset();

	if (!in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return SB_MAX_SIZE;
	}

	if (!havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return SB_MAX_SIZE;
	}

	uint8_t *pptr = in;

	sb_size_t i;
	for (i = havesize; i--;) {
		if (pptr[i]) {
			return i;
		}
	}

	return SB_MAX_SIZE;
}
