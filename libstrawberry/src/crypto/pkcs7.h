#ifndef __SB_CRYPTO_PKCS7_H
#define __SB_CRYPTO_PKCS7_H


#include <stdint.h>

#include "../core/sbapi.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI size_t sb_crypto_pkcs7_size(size_t blocksize, size_t havesize);
	SBAPI void sb_crypto_pkcs7(size_t blocksize, uint8_t *out, uint8_t *in, size_t havesize);
	SBAPI size_t sb_crypto_pkcs7_offset(size_t blocksize, uint8_t *in, size_t size);

#ifdef __cplusplus
}
#endif


#endif
