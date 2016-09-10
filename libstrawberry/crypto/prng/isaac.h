/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CRYPTO_PRNG_ISAAC_H
#define __SB_CRYPTO_PRNG_ISAAC_H


#include "../../core/stdincl.h"

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

	SBAPI void sb_crypto_prng_isaac_init_ex(sb_crypto_prng_isaac_ctx_t *ctx, sb_bool_t preseeded, uint64_t seednonce);
	SBAPI void sb_crypto_prng_isaac_clear(sb_crypto_prng_isaac_ctx_t *ctx);
	SBAPI void sb_crypto_prng_isaac_update(sb_crypto_prng_isaac_ctx_t *ctx);
	SBAPI uint32_t sb_crypto_prng_isaac(sb_crypto_prng_isaac_ctx_t *ctx);
	SBAPI uint32_t sb_crypto_prng_isaac_range(sb_crypto_prng_isaac_ctx_t *ctx, uint32_t min, uint32_t max);

#ifdef __cplusplus
}
#endif


#endif
