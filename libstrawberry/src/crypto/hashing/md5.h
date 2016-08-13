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

#ifndef __SB_CRYPTO_HASHING_MD5_H
#define __SB_CRYPTO_HASHING_MD5_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"


typedef struct sb_crypto_md5_ctx {
	uint32_t lo;
	uint32_t hi;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint8_t buffer[64];
	uint32_t block[16];
} sb_crypto_md5_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_md5_init(sb_crypto_md5_ctx_t *ctx);
	SBAPI void sb_crypto_md5_clear(sb_crypto_md5_ctx_t *ctx);
	SBAPI void sb_crypto_md5_update(sb_crypto_md5_ctx_t *ctx, void *in, sb_size_t size);
	SBAPI void sb_crypto_md5_finish(sb_crypto_md5_ctx_t *ctx, void *out);
	SBAPI void sb_crypto_md5(void *out, void *in, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
