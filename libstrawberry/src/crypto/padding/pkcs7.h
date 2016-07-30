#ifndef __SB_CRYPTO_PKCS7_H
#define __SB_CRYPTO_PKCS7_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_crypto_pad_pkcs7_size(sb_size_t blocksize, sb_size_t havesize);
	SBAPI void sb_crypto_pad_pkcs7(sb_size_t blocksize, uint8_t *out, uint8_t *in, sb_size_t havesize);
	SBAPI sb_size_t sb_crypto_pad_pkcs7_offset(sb_size_t blocksize, uint8_t *in, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
