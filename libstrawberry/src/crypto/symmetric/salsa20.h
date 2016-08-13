/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU Lesser General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU Lesser General Public License for more details.                          **
**                                                                               **
**  You should have received a copy of the GNU Lesser General Public License     **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

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
	SBAPI void sb_crypto_salsa20_nonce_increment(sb_crypto_salsa20_ctx_t *ctx);
	SBAPI void sb_crypto_salsa20_nonce_decrement(sb_crypto_salsa20_ctx_t *ctx);
	SBAPI void sb_crypto_salsa20_nonce_set(sb_crypto_salsa20_ctx_t *ctx, uint64_t nonce);
	SBAPI void sb_crypto_salsa20_process(sb_crypto_salsa20_ctx_t *ctx, void *out, void *in, sb_size_t size);
#	define sb_crypto_salsa20_encrypt		sb_crypto_salsa20_process
#	define sb_crypto_salsa20_decrypt		sb_crypto_salsa20_process

#ifdef __cplusplus
}
#endif


#endif
