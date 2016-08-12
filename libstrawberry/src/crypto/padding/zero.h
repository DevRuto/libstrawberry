#ifndef __SB_CRYPTO_PADDING_ZERO_H
#define __SB_CRYPTO_PADDING_ZERO_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_crypto_pad_zero_size(sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_bool_t sb_crypto_pad_zero(void *out, void *in, sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_size_t sb_crypto_pad_zero_offset(void *in, sb_size_t havesize);

#ifdef __cplusplus
}
#endif


#endif
