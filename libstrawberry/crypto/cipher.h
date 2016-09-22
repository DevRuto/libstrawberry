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

#ifndef __SB_CRYPTO_CIPHER_H
#define __SB_CRYPTO_CIPHER_H


#include "../core/stdincl.h"

#include "./blockmode.h"

#include "./symmetric/rijndael.h"
#include "./symmetric/salsa20.h"
#include "./symmetric/rabbit.h"

#include "./padding/zero.h"
#include "./padding/pkcs7.h"
#include "./padding/iso97971-2.h"


#define SB_CRYPTO_CIPHER_RIJNDAEL			1
#define SB_CRYPTO_CIPHER_SALSA20			2
#define SB_CRYPTO_CIPHER_RABBIT				3

#define SB_CRYPTO_CIPHER_PAD_ZERO			1
#define SB_CRYPTO_CIPHER_PAD_PKCS7			2
#define SB_CRYPTO_CIPHER_PAD_ISO979712		3


typedef struct sb_crypto_cipher_ctx {
	void *data;
	sb_crypto_blockmode_ctx_t *blockmode;
	uint16_t cipher;
	uint8_t padding;
	uint8_t flags;
} sb_crypto_cipher_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_crypto_cipher_get_blocksize(uint16_t cipher);

	// ------------------------------------------------------------------------

	SBAPI sb_bool_t sb_crypto_cipher_init(sb_crypto_cipher_ctx_t *ctx, uint16_t cipher, uint8_t padding, uint8_t flags, uint16_t bits, void *key);
	SBAPI sb_bool_t sb_crypto_cipher_reset(sb_crypto_cipher_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_cipher_clear(sb_crypto_cipher_ctx_t *ctx);

	SBAPI sb_bool_t sb_crypto_cipher_blockmode_init(sb_crypto_cipher_ctx_t *ctx, uint16_t mode, uint16_t flags, void *iv, sb_size_t ivsize);
	SBAPI sb_bool_t sb_crypto_cipher_blockmode_clear(sb_crypto_cipher_ctx_t *ctx);
	SBAPI sb_bool_t sb_crypto_cipher_blockmode_set(sb_crypto_cipher_ctx_t *ctx, sb_crypto_blockmode_ctx_t *blockmodectxptr);
	SBAPI sb_bool_t sb_crypto_cipher_blockmode_set_enabled(sb_crypto_cipher_ctx_t *ctx, sb_bool_t enabled);

	SBAPI sb_size_t sb_crypto_cipher_encrypt_size(sb_crypto_cipher_ctx_t *ctx, sb_size_t size);
	SBAPI sb_size_t sb_crypto_cipher_decrypt_size(sb_crypto_cipher_ctx_t *ctx, void *in, sb_size_t insize);

	SBAPI sb_bool_t sb_crypto_cipher_encrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size);
	SBAPI sb_bool_t sb_crypto_cipher_decrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size, sb_size_t *padoffset);

#ifdef __cplusplus
}
#endif


#endif
