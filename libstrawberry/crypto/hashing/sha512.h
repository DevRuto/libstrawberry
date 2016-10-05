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

#ifndef __SB_CRYPTO_HASHING_SHA512_H
#define __SB_CRYPTO_HASHING_SHA512_H


#include "../../core/stdincl.h"

typedef struct sb_crypto_sha512_ctx {
	uint64_t h0;
	uint64_t h1;
	uint64_t h2;
	uint64_t h3;
	uint64_t h4;
	uint64_t h5;
	uint64_t h6;
	uint64_t h7;
} sb_crypto_sha512_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_bool_t sb_crypto_sha512_init(sb_crypto_sha512_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_sha512_clear(sb_crypto_sha512_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_sha512_update(sb_crypto_sha512_ctx_t *ctx, uint64_t block[16]);
	SBAPI sb_bool_t sb_crypto_sha512_finish(sb_crypto_sha512_ctx_t *ctx, uint8_t out[64]);
	SBAPI sb_bool_t sb_crypto_sha512(uint8_t out[64], void *in, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
