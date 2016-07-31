#include "../../core/identid.h"
IDENTID("pkcs7.c", "0.1", "1", "2016-07-29");

#include "pkcs7.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/math.h"


size_t sb_crypto_pad_pkcs7_size(size_t blocksize, size_t havesize) {
	size_t size = sb_math_round_block(blocksize, havesize);
	if (size == havesize) {
		size += blocksize;
	}
	return size;
}

void sb_crypto_pad_pkcs7(size_t blocksize, uint8_t *out, uint8_t *in, size_t havesize) {
	sb_error_reset();

	if (!out || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	size_t size = sb_crypto_pad_pkcs7_size(blocksize, havesize);
	if (size <= havesize) {
		sb_error_set(SB_ERROR_FAILSAFE);
		return;
	}

	uint8_t pad = (uint8_t)(size - havesize), pidx = pad, *psptr = ((out + havesize) - 1);
	sb_memcpy(out, in, havesize);
	for (; pidx--;) {
		*(++psptr) = pad;
	}
}

size_t sb_crypto_pad_pkcs7_offset(size_t blocksize, uint8_t *in, size_t size) {
	sb_error_reset();

	if (size == 0) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return 0;
	}

	uint8_t pad = in[size - 1];
	if (pad > blocksize) {
		sb_error_set(SB_ERROR_FAILSAFE);
		return 0;
	} else {
		return (size - pad);
	}
}
