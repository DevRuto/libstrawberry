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

#ifndef __SB_CRYPTO_HASHING_MD5_H
#define __SB_CRYPTO_HASHING_MD5_H


#include "../../core/stdincl.h"


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
