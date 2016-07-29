#ifndef _SB_CRYPTO_PRNG_ISAAC_H
#define _SB_CRYPTO_PRNG_ISAAC_H


#include <stdint.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"


#define SB_CRYPTO_PRNG_ISAAC_SHIFT			8
#define SB_CRYPTO_PRNG_ISAAC_SIZE			(1 << SB_CRYPTO_PRNG_ISAAC_SHIFT)


typedef uint_fast32_t sb_crypto_prng_isaac_int_t;

typedef struct sb_crypto_prng_isaac_ctx {
	sb_crypto_prng_isaac_int_t cnt;
	sb_crypto_prng_isaac_int_t rsl[SB_CRYPTO_PRNG_ISAAC_SIZE];
	sb_crypto_prng_isaac_int_t mem[SB_CRYPTO_PRNG_ISAAC_SIZE];
	sb_crypto_prng_isaac_int_t a;
	sb_crypto_prng_isaac_int_t b;
	sb_crypto_prng_isaac_int_t c;
} sb_crypto_prng_isaac_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_prng_isaac_init(sb_crypto_prng_isaac_ctx_t *ctx, sb_bool_t preseeded);
	SBAPI void sb_crypto_prng_isaac_update(sb_crypto_prng_isaac_ctx_t *ctx);
	SBAPI sb_crypto_prng_isaac_int_t sb_crypto_prng_isaac(sb_crypto_prng_isaac_ctx_t *ctx);

#ifdef __cplusplus
}
#endif


#endif
