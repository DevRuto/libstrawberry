/*****************************************************************************
**                                                                          **
**  This file is part of libstrawberry.                                     **
**                                                                          **
**  libstrawberry is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by    **
**  the Free Software Foundation, either version 3 of the License, or       **
**  (at your option) any later version.                                     **
**                                                                          **
**  libstrawberry is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **
**  GNU General Public License for more details.                            **
**                                                                          **
**  You should have received a copy of the GNU General Public License       **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                          **
******************************************************************************
**
**  Notes:
**    -
**
*/

#include "../../core/identid.h"
IDENTID("salsa20.c", "0.1", "1", "2016-07-29");

#include "salsa20.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"


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

void sb_crypto_salsa20_process(sb_crypto_salsa20_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	sb_error_reset();

	if (!ctx || !out || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	if (!size) {
		sb_error_set(SB_ERROR_PARAM_RANGE);
		return;
	}

	uint8_t buffer[64], *optr = out, *iptr = in;
	uint32_t *buffer32 = (uint32_t*)buffer;

	ctx->layout.counter = 0;

	register uint32_t i,
		 x0,  x1,  x2,  x3,
		 x4,  x5,  x6,  x7,
		 x8,  x9, x10, x11,
		x12, x13, x14, x15;

	for (;;) {
		x0  = ctx->data[ 0];
		x1  = ctx->data[ 1];
		x2  = ctx->data[ 2];
		x3  = ctx->data[ 3];
		x4  = ctx->data[ 4];
		x5  = ctx->data[ 5];
		x6  = ctx->data[ 6];
		x7  = ctx->data[ 7];
		x8  = ctx->data[ 8];
		x9  = ctx->data[ 9];
		x10 = ctx->data[10];
		x11 = ctx->data[11];
		x12 = ctx->data[12];
		x13 = ctx->data[13];
		x14 = ctx->data[14];
		x15 = ctx->data[15];

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

		buffer32[ 0] = x0  + ctx->data[ 0];
		buffer32[ 1] = x1  + ctx->data[ 1];
		buffer32[ 2] = x2  + ctx->data[ 2];
		buffer32[ 3] = x3  + ctx->data[ 3];
		buffer32[ 4] = x4  + ctx->data[ 4];
		buffer32[ 5] = x5  + ctx->data[ 5];
		buffer32[ 6] = x6  + ctx->data[ 6];
		buffer32[ 7] = x7  + ctx->data[ 7];
		buffer32[ 8] = x8  + ctx->data[ 8];
		buffer32[ 9] = x9  + ctx->data[ 9];
		buffer32[10] = x10 + ctx->data[10];
		buffer32[11] = x11 + ctx->data[11];
		buffer32[12] = x12 + ctx->data[12];
		buffer32[13] = x13 + ctx->data[13];
		buffer32[14] = x14 + ctx->data[14];
		buffer32[15] = x15 + ctx->data[15];

		if (!++ctx->data[8]) {
			++ctx->data[9];
		}

		if (size <= 64) {
			for (i = 0; i < size; ++i) optr[i] = iptr[i] ^ buffer[i];
			return;
		}
		for (i = 0; i < 64; ++i) optr[i] = iptr[i] ^ buffer[i];
		size -= 64;
		optr += 64;
		iptr += 64;
	}
}
