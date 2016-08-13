/*****************************************************************************
**                                                                          **
**  This file is part of libstrawberry.                                     **
**                                                                          **
**  libstrawberry is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by    **
**  the Free Software Foundation, either version 3 of the License, or       **
**  (at your option) any later version.                                     **
**                                                                          **
**  libstrawberry is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **
**  GNU General Public License for more details.                            **
**                                                                          **
**  You should have received a copy of the GNU General Public License       **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                          **
******************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CRYPTO_PRNG_ISAAC_H
#define __SB_CRYPTO_PRNG_ISAAC_H


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
