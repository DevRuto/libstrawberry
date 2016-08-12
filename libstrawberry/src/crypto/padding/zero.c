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
	sb_memset(out + havesize, 0, size - havesize);

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
