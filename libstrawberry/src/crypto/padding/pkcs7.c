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

	uint8_t pad = (uint8_t)(size - havesize), pidx = pad, *pptr = ((out + havesize) - 1);
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
