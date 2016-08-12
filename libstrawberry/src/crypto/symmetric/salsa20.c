#include "../../core/identid.h"
IDENTID("salsa20.c", "0.1", "1", "2016-07-29");

#include "salsa20.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"


static void sb_crypto_salsa20_wordtobyte(uint32_t out[16], uint32_t in[16]) {
	register uint32_t i,
		x0  = in[ 0],
		x1  = in[ 1],
		x2  = in[ 2],
		x3  = in[ 3],
		x4  = in[ 4],
		x5  = in[ 5],
		x6  = in[ 6],
		x7  = in[ 7],
		x8  = in[ 8],
		x9  = in[ 9],
		x10 = in[10],
		x11 = in[11],
		x12 = in[12],
		x13 = in[13],
		x14 = in[14],
		x15 = in[15];

	for (i = 20; i > 0; i -= 2) {
		x4  ^= SB_ROTL32((x0  + x12),  7);
		x8  ^= SB_ROTL32((x4  + x0 ),  9);
		x12 ^= SB_ROTL32((x8  + x4 ), 13);
		x0  ^= SB_ROTL32((x12 + x8 ), 18);
		x9  ^= SB_ROTL32((x5  + x1 ),  7);
		x13 ^= SB_ROTL32((x9  + x5 ),  9);
		x1  ^= SB_ROTL32((x13 + x9 ), 13);
		x5  ^= SB_ROTL32((x1  + x13), 18);
		x14 ^= SB_ROTL32((x10 + x6 ),  7);
		x2  ^= SB_ROTL32((x14 + x10),  9);
		x6  ^= SB_ROTL32((x2  + x14), 13);
		x10 ^= SB_ROTL32((x6  + x2 ), 18);
		x3  ^= SB_ROTL32((x15 + x11),  7);
		x7  ^= SB_ROTL32((x3  + x15),  9);
		x11 ^= SB_ROTL32((x7  + x3 ), 13);
		x15 ^= SB_ROTL32((x11 + x7 ), 18);
		x1  ^= SB_ROTL32((x0  + x3 ),  7);
		x2  ^= SB_ROTL32((x1  + x0 ),  9);
		x3  ^= SB_ROTL32((x2  + x1 ), 13);
		x0  ^= SB_ROTL32((x3  + x2 ), 18);
		x6  ^= SB_ROTL32((x5  + x4 ),  7);
		x7  ^= SB_ROTL32((x6  + x5 ),  9);
		x4  ^= SB_ROTL32((x7  + x6 ), 13);
		x5  ^= SB_ROTL32((x4  + x7 ), 18);
		x11 ^= SB_ROTL32((x10 + x9 ),  7);
		x8  ^= SB_ROTL32((x11 + x10),  9);
		x9  ^= SB_ROTL32((x8  + x11), 13);
		x10 ^= SB_ROTL32((x9  + x8 ), 18);
		x12 ^= SB_ROTL32((x15 + x14),  7);
		x13 ^= SB_ROTL32((x12 + x15),  9);
		x14 ^= SB_ROTL32((x13 + x12), 13);
		x15 ^= SB_ROTL32((x14 + x13), 18);
	}

	out[ 0] = x0  + in[ 0];
	out[ 1] = x1  + in[ 1];
	out[ 2] = x2  + in[ 2];
	out[ 3] = x3  + in[ 3];
	out[ 4] = x4  + in[ 4];
	out[ 5] = x5  + in[ 5];
	out[ 6] = x6  + in[ 6];
	out[ 7] = x7  + in[ 7];
	out[ 8] = x8  + in[ 8];
	out[ 9] = x9  + in[ 9];
	out[10] = x10 + in[10];
	out[11] = x11 + in[11];
	out[12] = x12 + in[12];
	out[13] = x13 + in[13];
	out[14] = x14 + in[14];
	out[15] = x15 + in[15];
}


static const uint8_t sigma[16] = "expand 32-byte k";
static const uint8_t theta[16] = "expand 16-byte k";

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
		sb_crypto_salsa20_wordtobyte((uint32_t*)buffer, ctx->data);

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
