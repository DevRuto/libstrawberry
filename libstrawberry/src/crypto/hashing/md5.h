#ifndef _SB_CRYPTO_HASHING_MD5_H
#define _SB_CRYPTO_HASHING_MD5_H


#include <stdint.h>

#include "../../core/sbapi.h"


typedef struct sb_crypto_md5_ctx {
	uint32_t lo;
	uint32_t hi;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint8_t buffer[64];
	uint32_t block[16];
} sb_crypto_md5_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_md5_init(sb_crypto_md5_ctx_t *ctx);
	SBAPI void sb_crypto_md5_clear(sb_crypto_md5_ctx_t *ctx);
	SBAPI void sb_crypto_md5_update(sb_crypto_md5_ctx_t *ctx, void *in, size_t size);
	SBAPI void sb_crypto_md5_finish(sb_crypto_md5_ctx_t *ctx, void *out);
	SBAPI void sb_crypto_md5(void *out, void *in, size_t size);

#ifdef __cplusplus
}
#endif


#endif
