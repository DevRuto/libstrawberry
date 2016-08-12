#include "../../core/identid.h"
IDENTID("iso97971-2.c", "0.1", "1", "2016-08-12");

#include "iso97971-2.h"
#include "zero.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/math.h"
#include "../../core/bits.h"

sb_size_t sb_crypto_pad_iso979712_size(sb_size_t blocksize, sb_size_t havesize) {
	return sb_math_round_block(blocksize, havesize);
}

sb_bool_t sb_crypto_pad_iso979712(void *out, void *in, sb_size_t blocksize, sb_size_t havesize) {
	sb_error_reset();

	if (!out || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!blocksize || !havesize) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
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
			if (pptr[i] == SB_BIT_8) {
				return i;
			} else {
				sb_error_set(SB_ERROR_FAILSAFE);
				return SB_MAX_SIZE;
			}
		}
	}

	return SB_MAX_SIZE;
}
