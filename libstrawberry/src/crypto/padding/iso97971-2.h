#ifndef __SB_CRYPTO_PADDING_ISO979712
#define __SB_CRYPTO_PADDING_ISO979712


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_crypto_pad_iso979712_size(sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_bool_t sb_crypto_pad_iso979712(void *out, void *in, sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_size_t sb_crypto_pad_iso979712_offset(void *in, sb_size_t havesize);

#ifdef __cplusplus
}
#endif


#endif
