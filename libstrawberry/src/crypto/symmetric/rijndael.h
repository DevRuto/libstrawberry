/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU General Public License as published by         **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU General Public License for more details.                                 **
**                                                                               **
**  You should have received a copy of the GNU General Public License            **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CRYPTO_SYMMETRIC_RIJNDAEL_H
#define __SB_CRYPTO_SYMMETRIC_RIJNDAEL_H


#include <stdint.h>

#include "../../core/sbapi.h"

#include "../blockmode.h"


typedef struct sb_crypto_rijndael_ctx {
	uint32_t *key_encrypt;
	uint32_t *key_decrypt;
	uint8_t size;
	uint8_t rounds;
	uint16_t flags;
} sb_crypto_rijndael_ctx_t;


#define SB_CRYPTO_RIJNDAEL_BLOCK_SIZE		16

#define SB_CRYPTO_RIJNDAEL_128				1
#define SB_CRYPTO_RIJNDAEL_192				2
#define SB_CRYPTO_RIJNDAEL_256				3


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_rijndael_init(sb_crypto_rijndael_ctx_t *rijndael, uint8_t bits, void *key);
	SBAPI void sb_crypto_rijndael_clear(sb_crypto_rijndael_ctx_t *rijndael);
	SBAPI void sb_crypto_rijndael_encrypt_block(sb_crypto_rijndael_ctx_t *rijndael, void *out, void *in);
	SBAPI void sb_crypto_rijndael_decrypt_block(sb_crypto_rijndael_ctx_t *rijndael, void *out, void *in);

#ifdef __cplusplus
}
#endif


#endif
