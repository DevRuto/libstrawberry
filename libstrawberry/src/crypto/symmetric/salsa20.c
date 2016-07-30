#include "../../core/identid.h"
IDENTID("salsa20.c", "0.1", "1", "2016-07-29");

#include "salsa20.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"


static void sb_crypto_salsa20_wordtobyte(uint8_t out[64], uint32_t in[16]) {
	uint32_t X[16];
	sb_memcpy(X, in, sizeof(X));

	register uint32_t i;
	for (i = 20; i > 0; i -= 2) {
		X[ 4] ^= SB_ROTL32((X[ 0] + X[12]),  7);
		X[ 8] ^= SB_ROTL32((X[ 4] + X[ 0]),  9);
		X[12] ^= SB_ROTL32((X[ 8] + X[ 4]), 13);
		X[ 0] ^= SB_ROTL32((X[12] + X[ 8]), 18);
		X[ 9] ^= SB_ROTL32((X[ 5] + X[ 1]),  7);
		X[13] ^= SB_ROTL32((X[ 9] + X[ 5]),  9);
		X[ 1] ^= SB_ROTL32((X[13] + X[ 9]), 13);
		X[ 5] ^= SB_ROTL32((X[ 1] + X[13]), 18);
		X[14] ^= SB_ROTL32((X[10] + X[ 6]),  7);
		X[ 2] ^= SB_ROTL32((X[14] + X[10]),  9);
		X[ 6] ^= SB_ROTL32((X[ 2] + X[14]), 13);
		X[10] ^= SB_ROTL32((X[ 6] + X[ 2]), 18);
		X[ 3] ^= SB_ROTL32((X[15] + X[11]),  7);
		X[ 7] ^= SB_ROTL32((X[ 3] + X[15]),  9);
		X[11] ^= SB_ROTL32((X[ 7] + X[ 3]), 13);
		X[15] ^= SB_ROTL32((X[11] + X[ 7]), 18);
		X[ 1] ^= SB_ROTL32((X[ 0] + X[ 3]),  7);
		X[ 2] ^= SB_ROTL32((X[ 1] + X[ 0]),  9);
		X[ 3] ^= SB_ROTL32((X[ 2] + X[ 1]), 13);
		X[ 0] ^= SB_ROTL32((X[ 3] + X[ 2]), 18);
		X[ 6] ^= SB_ROTL32((X[ 5] + X[ 4]),  7);
		X[ 7] ^= SB_ROTL32((X[ 6] + X[ 5]),  9);
		X[ 4] ^= SB_ROTL32((X[ 7] + X[ 6]), 13);
		X[ 5] ^= SB_ROTL32((X[ 4] + X[ 7]), 18);
		X[11] ^= SB_ROTL32((X[10] + X[ 9]),  7);
		X[ 8] ^= SB_ROTL32((X[11] + X[10]),  9);
		X[ 9] ^= SB_ROTL32((X[ 8] + X[11]), 13);
		X[10] ^= SB_ROTL32((X[ 9] + X[ 8]), 18);
		X[12] ^= SB_ROTL32((X[15] + X[14]),  7);
		X[13] ^= SB_ROTL32((X[12] + X[15]),  9);
		X[14] ^= SB_ROTL32((X[13] + X[12]), 13);
		X[15] ^= SB_ROTL32((X[14] + X[13]), 18);
	}

	for (i = 16; i--;) X[i] += in[i];

	sb_memcpy(out, X, sizeof(X));
}


static const uint8_t sigma[16] = { 'e', 'x', 'p', 'a', 'n', 'd', ' ', '3', '2', '-', 'b', 'y', 't', 'e', ' ', 'k' };
static const uint8_t theta[16] = { 'e', 'x', 'p', 'a', 'n', 'd', ' ', '1', '6', '-', 'b', 'y', 't', 'e', ' ', 'k' };

void sb_crypto_salsa20_init_ex(sb_crypto_salsa20_ctx_t *ctx, uint8_t bits, void *key, void *nonce, void *constant) {
	sb_error_reset();

	if (!ctx || !key) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	sb_crypto_salsa20_clear(ctx);

	uint32_t *k32 = (uint32_t*)key;
	sb_memcpy(ctx->layout.k1, k32, sizeof(ctx->layout.k1));

	const uint8_t *c = constant;
	if (bits == SB_CRYPTO_SALSA20_128) {
		if (!c) {
			c = theta;
		}
	} else if (bits == SB_CRYPTO_SALSA20_256) {
		k32 += 16;
		if (!c) {
			c = sigma;
		}
	} else {
		sb_crypto_salsa20_clear(ctx);
		sb_error_set(SB_ERROR_PARAM_INVALID);
		return;
	}

	sb_memcpy(ctx->layout.k2, k32, sizeof(ctx->layout.k2));

	uint32_t *c32 = (uint32_t*)(constant ? constant : c);
	ctx->layout.c1 = c32[0];
	ctx->layout.c2 = c32[1];
	ctx->layout.c3 = c32[2];
	ctx->layout.c4 = c32[3];

	if (nonce) {
		sb_memcpy(&ctx->layout.nonce, nonce, sizeof(ctx->layout.nonce));
	}
}

void sb_crypto_salsa20_init(sb_crypto_salsa20_ctx_t *ctx, uint8_t bits, void *key, void *nonce) {
	sb_crypto_salsa20_init_ex(ctx, bits, key, nonce, NULL);
}

void sb_crypto_salsa20_clear(sb_crypto_salsa20_ctx_t *ctx) {
	sb_error_reset();
	if (ctx) {
		sb_memset(ctx, 0, sizeof(*ctx));
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}


void sb_crypto_salsa20_encrypt(sb_crypto_salsa20_ctx_t *ctx, uint8_t *plain, uint8_t *cipher, sb_size_t size) {
	sb_error_reset();

	if (!ctx || !plain || !cipher) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	if (!size) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return;
	}

	uint8_t buffer[64];

	ctx->layout.counter = 0;

	register uint32_t i;
	for (;;) {
		sb_crypto_salsa20_wordtobyte(buffer, ctx->data);

		if (!++ctx->data[8]) {
			++ctx->data[9];
		}

		if (size <= 64) {
			for (i = 0; i < size; ++i) cipher[i] = plain[i] ^ buffer[i];
			return;
		}
		for (i = 0; i < 64; ++i) cipher[i] = plain[i] ^ buffer[i];
		size -= 64;
		cipher += 64;
		plain += 64;
	}
}

void sb_crypto_salsa20_decrypt(sb_crypto_salsa20_ctx_t *ctx, uint8_t *cipher, uint8_t *plain, sb_size_t size) {
	sb_crypto_salsa20_encrypt(ctx, cipher, plain, size);
}


void sb_crypto_salsa20_nonce_increment(sb_crypto_salsa20_ctx_t *ctx) {
	sb_error_reset();
	if (ctx) {
		++ctx->layout.nonce;
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}

SBAPI void sb_crypto_salsa20_nonce_decrement(sb_crypto_salsa20_ctx_t *ctx) {
	sb_error_reset();
	if (ctx) {
		--ctx->layout.nonce;
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}

SBAPI void sb_crypto_salsa20_nonce_set(sb_crypto_salsa20_ctx_t *ctx, uint64_t nonce) {
	sb_error_reset();
	if (ctx) {
		ctx->layout.nonce = nonce;
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}
