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

#include "../core/identid.h"
IDENTID("cipher.c", "0.1", "1", "2016-08-23");

#include "cipher.h"

#include "../core/error.h"
#include "../core/memory.h"

#include "symmetric/rijndael.h"
#include "symmetric/salsa20.h"
#include "symmetric/rabbit.h"


sb_size_t sb_crypto_cipher_get_blocksize(uint16_t cipher) {
	switch (cipher) {
		case SB_CRYPTO_CIPHER_RIJNDAEL:
			return SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
		case SB_CRYPTO_CIPHER_SALSA20:
			return SB_CRYPTO_BLOCKSIZE_SALSA20;
		case SB_CRYPTO_CIPHER_RABBIT:
			return SB_CRYPTO_BLOCKSIZE_RABBIT;
		default:
			return 0;
	}
}

sb_bool_t sb_crypto_cipher_init(sb_crypto_cipher_ctx_t *ctx, uint16_t cipher, uint16_t flags, uint8_t bits, void *key) {
	if (!ctx || !cipher) {
		return sb_false;
	}

	sb_memset(ctx, 0, sizeof(*ctx));

	switch (cipher) {
		case SB_CRYPTO_CIPHER_RIJNDAEL:
			ctx->data = sb_malloc_s(sizeof(sb_crypto_rijndael_ctx_t));
			sb_crypto_rijndael_init(ctx->data, bits, key);
			break;
		case SB_CRYPTO_CIPHER_SALSA20:
			ctx->data = sb_malloc_s(sizeof(sb_crypto_salsa20_ctx_t));
			sb_crypto_salsa20_init(ctx->data, bits, key, NULL);
			break;
		case SB_CRYPTO_CIPHER_RABBIT:
			ctx->data = sb_malloc_s(sizeof(sb_crypto_rabbit_ctx_t));
			sb_crypto_rabbit_init(ctx->data, key, 0);
			break;
		default:
			return sb_false;
	}

	ctx->cipher = cipher;
	ctx->flags = flags;

	return sb_true;
}

sb_bool_t sb_crypto_cipher_reset(sb_crypto_cipher_ctx_t *ctx) {
	if (!ctx || !ctx->cipher || !ctx->data) {
		return sb_false;
	}

	switch (ctx->cipher) {
		case SB_CRYPTO_CIPHER_RABBIT:
			sb_crypto_rabbit_reset(ctx->data);
			break;
		default:
			break;
	}

	return sb_true;
}

sb_bool_t sb_crypto_cipher_clear(sb_crypto_cipher_ctx_t *ctx) {
	if (!ctx || !ctx->cipher) {
		return sb_false;
	}

	if (ctx->data) {
		sb_bool_t clear_success = sb_false;
		switch (ctx->cipher) {
			case SB_CRYPTO_CIPHER_RIJNDAEL:
				clear_success = sb_crypto_rijndael_clear(ctx->data);
				break;
			case SB_CRYPTO_CIPHER_SALSA20:
				clear_success = sb_crypto_salsa20_clear(ctx->data);
				break;
			case SB_CRYPTO_CIPHER_RABBIT:
				clear_success = sb_crypto_rabbit_clear(ctx->data);
				break;
			default:
				return sb_false;
		}
		if (clear_success) {
			sb_free(ctx->data);
		} else {
			return sb_false;
		}
	}

	sb_memset(ctx, 0, sizeof(*ctx));

	return sb_true;
}

sb_bool_t sb_crypto_cipher_blockmode_init(sb_crypto_cipher_ctx_t *ctx, uint16_t mode, uint16_t flags, void *iv, sb_size_t ivsize) {
	return sb_false;
}

sb_bool_t sb_crypto_cipher_blockmode_clear(sb_crypto_cipher_ctx_t *ctx) {
	return sb_false;
}

sb_bool_t sb_crypto_cipher_blockmode_set(sb_crypto_cipher_ctx_t *ctx, sb_crypto_blockmode_ctx_t *blockmodectxptr) {
	return sb_false;
}

sb_bool_t sb_crypto_cipher_blockmode_set_enabled(sb_crypto_cipher_ctx_t *ctx, sb_bool_t enabled) {
	return sb_false;
}

sb_bool_t sb_crypto_cipher_encrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	return sb_false;
}

sb_bool_t sb_crypto_cipher_decrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	return sb_false;
}
