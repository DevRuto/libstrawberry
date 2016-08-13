#ifndef __SB_CRYPTO_SYMMETRIC_RABBIT_H
#define __SB_CRYPTO_SYMMETRIC_RABBIT_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"


typedef struct sb_crypto_rabbit_subctx {
	uint32_t x[8];
	uint32_t c[8];
	uint32_t carry;
} sb_crypto_rabbit_subctx_t;

typedef struct sb_crypto_rabbit_ctx {
	sb_crypto_rabbit_subctx_t initctx;
	sb_crypto_rabbit_subctx_t workctx;
} sb_crypto_rabbit_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_bool_t sb_crypto_rabbit_init(sb_crypto_rabbit_ctx_t *ctx, void *key, uint64_t iv);
	SBAPI sb_bool_t sb_crypto_rabbit_clear(sb_crypto_rabbit_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_rabbit_reset(sb_crypto_rabbit_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_rabbit_process(sb_crypto_rabbit_ctx_t *ctx, void *out, void *in, sb_size_t size);
#	define sb_crypto_rabbit_encrypt			sb_crypto_rabbit_process
#	define sb_crypto_rabbit_decrypt			sb_crypto_rabbit_process

#ifdef __cplusplus
}
#endif


#endif
