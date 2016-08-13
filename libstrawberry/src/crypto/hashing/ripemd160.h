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

#ifndef __SB_CRYPTO_HASHING_RIPEMD160_H
#define __SB_CRYPTO_HASHING_RIPEMD160_H


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
