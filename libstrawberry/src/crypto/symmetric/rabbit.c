/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU General Public License as published by         **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU General Public License for more details.                                 **
**                                                                               **
**  You should have received a copy of the GNU General Public License            **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    It works, but I feel like it really could use some polishing. // TODO
**
*/

#include "../../core/identid.h"
IDENTID("rabbit.c", "0.1", "1", "2016-08-12");

#include "rabbit.h"
#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"
#include <stdio.h>


static void sb_crypto_rabbit_next_state(sb_crypto_rabbit_subctx_t *subctx) {
	if (!subctx) {
		return;
	}

	uint32_t g[8], c[8], i;

	for (i = 8; i--;) {
		c[i] = subctx->c[i];
	}

	subctx->c[0] = (0x4D34D34D + subctx->c[0] +  subctx->carry       );
	subctx->c[1] = (0xD34D34D3 + subctx->c[1] + (subctx->c[0] < c[0]));
	subctx->c[2] = (0x34D34D34 + subctx->c[2] + (subctx->c[1] < c[1]));
	subctx->c[3] = (0x4D34D34D + subctx->c[3] + (subctx->c[2] < c[2]));
	subctx->c[4] = (0xD34D34D3 + subctx->c[4] + (subctx->c[3] < c[3]));
	subctx->c[5] = (0x34D34D34 + subctx->c[5] + (subctx->c[4] < c[4]));
	subctx->c[6] = (0x4D34D34D + subctx->c[6] + (subctx->c[5] < c[5]));
	subctx->c[7] = (0xD34D34D3 + subctx->c[7] + (subctx->c[6] < c[6]));

	subctx->carry = (subctx->c[7] < c[7]);

	uint32_t x, h, l;
	for (i = 8; i--;) {
		x = (subctx->x[i] + subctx->c[i]);
		h = ((x >> 16) & 0xFFFF);
		l = (x & 0xFFFF);
		g[i] = (SB_XOR((((((l * l) >> 17) + (l * h)) >> 15) + (h * h)), (x * x)));
	}

	subctx->x[0] = (g[0] + SB_ROTL32(g[7], 16) + SB_ROTL32(g[6], 16));
	subctx->x[1] = (g[1] + SB_ROTL32(g[0],  8) +           g[7]     );
	subctx->x[2] = (g[2] + SB_ROTL32(g[1], 16) + SB_ROTL32(g[0], 16));
	subctx->x[3] = (g[3] + SB_ROTL32(g[2],  8) +           g[1]     );
	subctx->x[4] = (g[4] + SB_ROTL32(g[3], 16) + SB_ROTL32(g[2], 16));
	subctx->x[5] = (g[5] + SB_ROTL32(g[4],  8) +           g[3]     );
	subctx->x[6] = (g[6] + SB_ROTL32(g[5], 16) + SB_ROTL32(g[4], 16));
	subctx->x[7] = (g[7] + SB_ROTL32(g[6],  8) +           g[5]     );
}

static void sb_crypto_rabbit_set_key(sb_crypto_rabbit_ctx_t *ctx, uint32_t key[4]) {
	ctx->initctx.carry = 0;

	uint8_t *bkey = (uint8_t*)key;
	uint16_t kparts[8];
	uint32_t i;
	for (i = 0; i < 8; ++i) {
		kparts[7 - i] = SB_LE16(bkey[(2 * i)] << 8 | bkey[(2 * i) + 1]);
	}

	for (i = 0; i < 8; ++i) {
		if ((i % 2) == 0) {
			ctx->initctx.x[i] = SB_16M32(kparts[(i + 1) % 8], kparts[i]);
			ctx->initctx.c[i] = SB_16M32(kparts[(i + 4) % 8], kparts[(i + 5) % 8]);
		} else {
			ctx->initctx.x[i] = SB_16M32(kparts[(i + 5) % 8], kparts[(i + 4) % 8]);
			ctx->initctx.c[i] = SB_16M32(kparts[i], kparts[(i + 1) % 8]);
		}
	}

	sb_crypto_rabbit_next_state(&ctx->initctx);
	sb_crypto_rabbit_next_state(&ctx->initctx);
	sb_crypto_rabbit_next_state(&ctx->initctx);
	sb_crypto_rabbit_next_state(&ctx->initctx);

	for (i = 8; i--;) {
		ctx->initctx.c[i] ^= ctx->initctx.x[(i + 4) & 7];
	}

	sb_crypto_rabbit_reset(ctx);
}

void sb_crypto_rabbit_set_iv(sb_crypto_rabbit_ctx_t *ctx, uint64_t iv) {
	uint32_t _iv[2],
			 i0, i1, i2, i3;

	*(uint64_t*)_iv = iv;
	i0 = SB_LE32(_iv[0]);
	i2 = SB_LE32(_iv[1]);
	i1 = ((i0 >> 16) | (i2 & 0xFFFF0000));
	i3 = ((i2 << 16) | (i0 & 0x0000FFFF));

	ctx->workctx.c[0] = SB_XOR(ctx->initctx.c[0], i0);
	ctx->workctx.c[1] = SB_XOR(ctx->initctx.c[1], i1);
	ctx->workctx.c[2] = SB_XOR(ctx->initctx.c[2], i2);
	ctx->workctx.c[3] = SB_XOR(ctx->initctx.c[3], i3);
	ctx->workctx.c[4] = SB_XOR(ctx->initctx.c[4], i0);
	ctx->workctx.c[5] = SB_XOR(ctx->initctx.c[5], i1);
	ctx->workctx.c[6] = SB_XOR(ctx->initctx.c[6], i2);
	ctx->workctx.c[7] = SB_XOR(ctx->initctx.c[7], i3);

	sb_memcpy(ctx->workctx.x, ctx->initctx.x, sizeof(ctx->workctx.x));

	ctx->workctx.carry = ctx->initctx.carry;

	sb_crypto_rabbit_next_state(&ctx->workctx);
	sb_crypto_rabbit_next_state(&ctx->workctx);
	sb_crypto_rabbit_next_state(&ctx->workctx);
	sb_crypto_rabbit_next_state(&ctx->workctx);
}

sb_bool_t sb_crypto_rabbit_init(sb_crypto_rabbit_ctx_t *ctx, void *key, uint64_t iv) {
	if (!ctx || !key) {
		return sb_false;
	}

	sb_crypto_rabbit_set_key(ctx, key);
	if (iv) {
		sb_crypto_rabbit_set_iv(ctx, iv);
	}

	return sb_true;
}

sb_bool_t sb_crypto_rabbit_reset(sb_crypto_rabbit_ctx_t *ctx) {
	if (!ctx) {
		return sb_false;
	}

	sb_memcpy(&ctx->workctx, &ctx->initctx, sizeof(ctx->workctx));

	return sb_true;
}

sb_bool_t sb_crypto_rabbit_clear(sb_crypto_rabbit_ctx_t *ctx) {
	if (!ctx) {
		return sb_false;
	}

	sb_memset(ctx, 0, sizeof(*ctx));

	return sb_true;
}

static void get_s(sb_crypto_rabbit_ctx_t *ctx, uint32_t *s_out) {
	uint32_t i;
	uint16_t *s16 = (uint16_t*)s_out, buffer;
	for (i = 0; i < 8; ++i) {
		if ((i % 2) == 0) {
			buffer = (((ctx->workctx.x[6 - i] >> 16) & 0xFFFF) ^ (ctx->workctx.x[(9 - i) % 8] & 0xFFFF));
		} else {
			buffer = ((ctx->workctx.x[7 - i] & 0xFFFF) ^ ((ctx->workctx.x[(12 - i) % 8] >> 16) & 0xFFFF));
		}
		s16[i] = SB_BE16(buffer);
	}
}

sb_bool_t sb_crypto_rabbit_process(sb_crypto_rabbit_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	if (!ctx || !out || !in) {
		return sb_false;
	}

	uint32_t *optr = out, *iptr = in, s[4];
	for (; size >= 16; size -= 16, optr += 4, iptr += 4) {
		sb_crypto_rabbit_next_state(&ctx->workctx);

		get_s(ctx, s);

		optr[0] = SB_XOR(iptr[0], s[0]);
		optr[1] = SB_XOR(iptr[1], s[1]);
		optr[2] = SB_XOR(iptr[2], s[2]);
		optr[3] = SB_XOR(iptr[3], s[3]);
	}

	if (size) {
		uint8_t *obptr = (uint8_t*)optr, *ibptr = (uint8_t*)iptr, *sb = (uint8_t*)s;

		sb_crypto_rabbit_next_state(&ctx->workctx);

		get_s(ctx, s);

		uint32_t i;
		for (i = size; i--;) {
			obptr[i] = SB_XOR(ibptr[i], sb[i]);
		}
	}

	return sb_true;
}
