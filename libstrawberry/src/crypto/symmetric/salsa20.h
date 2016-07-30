#ifndef __SB_CRYPTO_SYMMETRIC_SALSA20_H
#define __SB_CRYPTO_SYMMETRIC_SALSA20_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"


typedef struct sb_crypto_salsa20_ctx_layout {
	uint32_t c1;
	uint32_t k1[4];
	uint32_t c2;
	uint64_t nonce;
	uint64_t counter;
	uint32_t c3;
	uint32_t k2[4];
	uint32_t c4;
} sb_crypto_salsa20_ctx_layout_t;

typedef union sb_crypto_salsa20_ctx {
	uint32_t data[16];
	sb_crypto_salsa20_ctx_layout_t layout;
} sb_crypto_salsa20_ctx_t;


#define SB_CRYPTO_SALSA20_128				1
#define SB_CRYPTO_SALSA20_256				2


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_salsa20_init_ex(sb_crypto_salsa20_ctx_t *ctx, uint8_t bits, void *key, void *nonce, void *constant);
	SBAPI void sb_crypto_salsa20_init(sb_crypto_salsa20_ctx_t *ctx, uint8_t bits, void *key, void *nonce);
	SBAPI void sb_crypto_salsa20_clear(sb_crypto_salsa20_ctx_t *ctx);
	SBAPI void sb_crypto_salsa20_encrypt(sb_crypto_salsa20_ctx_t *ctx, uint8_t *plain, uint8_t *cipher, size_t size);
	SBAPI void sb_crypto_salsa20_decrypt(sb_crypto_salsa20_ctx_t *ctx, uint8_t *cipher, uint8_t *plain, size_t size);
	SBAPI void sb_crypto_salsa20_nonce_increment(sb_crypto_salsa20_ctx_t *ctx);
	SBAPI void sb_crypto_salsa20_nonce_decrement(sb_crypto_salsa20_ctx_t *ctx);
	SBAPI void sb_crypto_salsa20_nonce_set(sb_crypto_salsa20_ctx_t *ctx, uint64_t nonce);

#ifdef __cplusplus
}
#endif


#endif
