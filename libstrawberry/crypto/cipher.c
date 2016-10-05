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

#define __FILE_LOCAL__						"crypto/cipher.c"

#ifndef SB_EXCLUDE_CRYPTO_CIPHER

#include "./cipher.h"

#include "../core/error.h"
#include "../core/memory.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-08-23");


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


sb_bool_t sb_crypto_cipher_init(sb_crypto_cipher_ctx_t *ctx, uint16_t cipher, uint8_t padding, uint8_t flags, uint16_t bits, void *key) {
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
	ctx->padding = padding;
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
			ctx->data = sb_free(ctx->data);
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


sb_size_t sb_crypto_cipher_encrypt_size(sb_crypto_cipher_ctx_t *ctx, sb_size_t size) {
	sb_size_t blocksize = sb_crypto_cipher_get_blocksize(ctx->cipher);
	switch (ctx->padding) {
		case SB_CRYPTO_CIPHER_PAD_ZERO:
			return sb_crypto_pad_zero_size(blocksize, size);
		case SB_CRYPTO_CIPHER_PAD_PKCS7:
			return sb_crypto_pad_pkcs7_size(blocksize, size);
		case SB_CRYPTO_CIPHER_PAD_ISO979712:
			return sb_crypto_pad_iso979712_size(blocksize, size);
		default:
			return blocksize;
	}
}


sb_size_t sb_crypto_cipher_decrypt_size(sb_crypto_cipher_ctx_t *ctx, void *in, sb_size_t insize) {
	switch (ctx->padding) {
		case SB_CRYPTO_CIPHER_PAD_ZERO:
			return sb_crypto_pad_zero_offset(in, insize);
		case SB_CRYPTO_CIPHER_PAD_PKCS7:
			return sb_crypto_pad_pkcs7_offset(in, insize);
		case SB_CRYPTO_CIPHER_PAD_ISO979712:
			return sb_crypto_pad_iso979712_offset(in, insize);
		default:
			return 0;
	}
}


#define CRYPT_CHECK()													\
	sb_error_reset();													\
																		\
	if (!ctx) {															\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);							\
		return sb_false;												\
	}																	\
																		\
	if (!ctx->cipher) {													\
		sb_error_set_ex(SB_ERROR_PARAM_INVALID, 1);						\
		return sb_false;												\
	}																	\
																		\
	if (!ctx->data) {													\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);							\
		return sb_false;												\
	}																	\
																		\
	if (!out) {															\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 3);							\
		return sb_false;												\
	}																	\
																		\
	if (!in) {															\
		sb_error_set_ex(SB_ERROR_NULL_PTR, 4);							\
		return sb_false;												\
	}																	\
																		\
	if (!size) {														\
		sb_error_set_ex(SB_ERROR_PARAM_INVALID, 2);						\
		return sb_false;												\
	}																	\
																		\
	sb_size_t blocksize = sb_crypto_cipher_get_blocksize(ctx->cipher);	\
	if (!blocksize) {													\
		sb_error_set(SB_ERROR_VALUE_INVALID);							\
		return sb_false;												\
	}


sb_bool_t sb_crypto_cipher_encrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	CRYPT_CHECK();

	SB_MEM_BUFFER_ALLOC(uint8_t, buffer, blocksize);
	sb_memset(buffer, 0, blocksize);

	uint8_t *optr = out, *iptr = in;

	switch (ctx->cipher) {
		case SB_CRYPTO_CIPHER_RIJNDAEL:
			for (; size > SB_CRYPTO_BLOCKSIZE_RIJNDAEL;) {
				sb_crypto_rijndael_encrypt_block(ctx->data, buffer, iptr);

				// TODO: block mode of operation

				sb_memcpy(optr, buffer, blocksize);

				iptr += SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
				optr += SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
				size -= SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
			}

			sb_memcpy(buffer, iptr, size);
			sb_memset((buffer + size), 0, (blocksize - size));

			switch (ctx->padding) {
				case SB_CRYPTO_CIPHER_PAD_ZERO:
					sb_crypto_pad_zero(buffer, iptr, blocksize, size);
					break;
				case SB_CRYPTO_CIPHER_PAD_PKCS7:
					sb_crypto_pad_pkcs7(buffer, iptr, blocksize, size);
					break;
				case SB_CRYPTO_CIPHER_PAD_ISO979712:
					sb_crypto_pad_iso979712(buffer, iptr, blocksize, size);
					break;
				default:
					sb_error_set(SB_ERROR_VALUE_INVALID);
					SB_MEM_BUFFER_FREE(buffer);
					return sb_false;
			}

			sb_crypto_rijndael_encrypt_block(ctx->data, buffer, buffer);

			// TODO: block mode of operation

			sb_memcpy(optr, buffer, blocksize);
			break;
		case SB_CRYPTO_CIPHER_SALSA20:
		case SB_CRYPTO_CIPHER_RABBIT:
		default:
			SB_MEM_BUFFER_FREE(buffer);
			return sb_false;
	}

	SB_MEM_BUFFER_FREE(buffer);
	return sb_true;
}


sb_bool_t sb_crypto_cipher_decrypt(sb_crypto_cipher_ctx_t *ctx, void *out, void *in, sb_size_t size, sb_size_t *padoffset) {
	CRYPT_CHECK();

	SB_MEM_BUFFER_ALLOC(uint8_t, buffer, blocksize);
	sb_memset(buffer, 0, blocksize);

	sb_size_t origsize = size;
	uint8_t *optr = out, *iptr = in;

	switch (ctx->cipher) {
		case SB_CRYPTO_CIPHER_RIJNDAEL:
			for (; size > SB_CRYPTO_BLOCKSIZE_RIJNDAEL;) {
				sb_memcpy(buffer, iptr, SB_CRYPTO_BLOCKSIZE_RIJNDAEL); // TODO: block mode of operation

				sb_crypto_rijndael_decrypt_block(ctx->data, optr, buffer);

				iptr += SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
				optr += SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
				size -= SB_CRYPTO_BLOCKSIZE_RIJNDAEL;
			}

			sb_memcpy(buffer, iptr, size);
			sb_memset((buffer + size), 0, (blocksize - size));

			// TODO: block mode of operation

			sb_crypto_rijndael_decrypt_block(ctx->data, optr, buffer);
			break;
		case SB_CRYPTO_CIPHER_SALSA20:
		case SB_CRYPTO_CIPHER_RABBIT:
		default:
			SB_MEM_BUFFER_FREE(buffer);
			return sb_false;
	}

	if (padoffset) {
		*padoffset = sb_crypto_cipher_decrypt_size(ctx, out, origsize);
	}

	SB_MEM_BUFFER_FREE(buffer);
	return sb_true;
}


#undef CRYPT_CHECK

#else
#	ifdef REPORT_EXCLUSION
#		pragma message("Excluded: "__FILE_LOCAL__)
#	endif
#endif
