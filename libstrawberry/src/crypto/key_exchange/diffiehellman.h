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

#ifndef __SB_CRYPTO_ASYMMETRIC_DIFFIEHELLMAN_H
#define __SB_CRYPTO_ASYMMETRIC_DIFFIEHELLMAN_H


#include "../../core/stdincl.h"


#define SB_CRYPTO_DIFFIEHELLMAN_DEFAULT_BITCOUNT \
											1536


typedef struct __sb_crypto_diffiehellman_ctx __sb_crypto_diffiehellman_ctx_t;
typedef struct sb_crypto_diffiehellman_ctx {
	__sb_crypto_diffiehellman_ctx_t *data;
	uint16_t bits;
} sb_crypto_diffiehellman_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_bool_t sb_crypto_diffiehellman_init(sb_crypto_diffiehellman_ctx_t *ctx, uint16_t bits, uint64_t seed);
	SBAPI sb_bool_t sb_crypto_diffiehellman_clear(sb_crypto_diffiehellman_ctx_t *ctx);

	SBAPI sb_bool_t sb_crypto_diffiehellman_generate_base(sb_crypto_diffiehellman_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_diffiehellman_generate_keys(sb_crypto_diffiehellman_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_diffiehellman_generate(sb_crypto_diffiehellman_ctx_t *ctx);

	SBAPI sb_bool_t sb_crypto_diffiehellman_generate_secret(sb_crypto_diffiehellman_ctx_t *ctx, void *pk_bob);

	SBAPI sb_bool_t sb_crypto_diffiehellman_copy_base(sb_crypto_diffiehellman_ctx_t *dst, sb_crypto_diffiehellman_ctx_t *src);
	SBAPI sb_bool_t sb_crypto_diffiehellman_copy_keys(sb_crypto_diffiehellman_ctx_t *dst, sb_crypto_diffiehellman_ctx_t *src);

	#define sb_crypto_diffiehellman_port_size(ctx) (((ctx) && ((ctx)->bits)) ? (((ctx)->bits) / 8) : 0)

	SBAPI sb_bool_t sb_crypto_diffiehellman_import_generator(sb_crypto_diffiehellman_ctx_t *ctx, void *in);
	SBAPI sb_bool_t sb_crypto_diffiehellman_import_modulo(sb_crypto_diffiehellman_ctx_t *ctx, void *in);
	SBAPI sb_bool_t sb_crypto_diffiehellman_import_public(sb_crypto_diffiehellman_ctx_t *ctx, void *in);

	SBAPI sb_bool_t sb_crypto_diffiehellman_export_generator(sb_crypto_diffiehellman_ctx_t *ctx, void *out);
	SBAPI sb_bool_t sb_crypto_diffiehellman_export_modulo(sb_crypto_diffiehellman_ctx_t *ctx, void *out);
	SBAPI sb_bool_t sb_crypto_diffiehellman_export_public(sb_crypto_diffiehellman_ctx_t *ctx, void *out);
	SBAPI sb_bool_t sb_crypto_diffiehellman_export_secret(sb_crypto_diffiehellman_ctx_t *ctx, void *out);

#ifdef __cplusplus
}
#endif


#endif
