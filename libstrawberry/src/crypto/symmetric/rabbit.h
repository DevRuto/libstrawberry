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
