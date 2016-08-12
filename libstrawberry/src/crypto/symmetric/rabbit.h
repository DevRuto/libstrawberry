#ifndef __SB_CRYPTO_SYMMETRIC_RABBIT_H
#define __SB_CRYPTO_SYMMETRIC_RABBIT_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"


typedef struct sb_crypto_rabbit_subctx {
	uint32_t carry;
	uint32_t x[8];
	uint32_t c[8];
} sb_crypto_rabbit_subctx_t;

typedef struct sb_crypto_rabbit_ctx {
	sb_crypto_rabbit_subctx_t subctx;
	sb_crypto_rabbit_subctx_t wsubctx;
} sb_crypto_rabbit_ctx_t;


#endif
