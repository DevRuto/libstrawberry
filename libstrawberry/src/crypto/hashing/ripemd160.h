#ifndef __SB_CRYPTO_HASHING_RIPEMD_H
#define __SB_CRYPTO_HASHING_RIPEMD_H


#include <stdint.h>

#include "../../core/sbapi.h"
#include "../../core/bits.h"
#include "../../core/types/bool.h"


typedef struct sb_crypto_ripemd160_ctx {
	uint32_t data[5];
} sb_crypto_ripemd160_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_ripemd160_init(sb_crypto_ripemd160_ctx_t *ctx);
	SBAPI void sb_crypto_ripemd160_clear(sb_crypto_ripemd160_ctx_t *ctx);
	SBAPI void sb_crypto_ripemd160_update(sb_crypto_ripemd160_ctx_t *ctx, uint32_t X[16]);
	SBAPI void sb_crypto_ripemd160_finish(sb_crypto_ripemd160_ctx_t *ctx, void *in, sb_size_t size);
	SBAPI void sb_crypto_ripemd160(uint8_t digest[20], void *data, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
