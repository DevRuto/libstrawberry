#ifndef _SB_CRYPTO_PRNG_ISAAC_H
#define _SB_CRYPTO_PRNG_ISAAC_H


#include <stdint.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"
#include "../../core/math.h"


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
	SBAPI uint32_t sb_crypto_prng_isaac(sb_crypto_prng_isaac_ctx_t *ctx);
	SBAPI uint32_t sb_crypto_prng_isaac_range(sb_crypto_prng_isaac_ctx_t *ctx, uint32_t min, uint32_t max);

#ifdef __cplusplus
}
#endif


#endif
