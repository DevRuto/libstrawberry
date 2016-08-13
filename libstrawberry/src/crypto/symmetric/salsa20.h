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
