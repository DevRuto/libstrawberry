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
	SBAPI sb_bool_t sb_crypto_rabbit_set_iv(sb_crypto_rabbit_ctx_t *ctx, uint64_t iv);
	SBAPI sb_bool_t sb_crypto_rabbit_clear(sb_crypto_rabbit_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_rabbit_reset(sb_crypto_rabbit_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_rabbit_process(sb_crypto_rabbit_ctx_t *ctx, void *out, void *in, sb_size_t size);
#	define sb_crypto_rabbit_encrypt			sb_crypto_rabbit_process
#	define sb_crypto_rabbit_decrypt			sb_crypto_rabbit_process

#ifdef __cplusplus
}
#endif


#endif
