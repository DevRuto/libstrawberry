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
