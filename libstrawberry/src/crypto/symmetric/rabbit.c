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
	uint32_t i,
		k0 = SB_LE32(key[0]),
		k1 = SB_LE32(key[1]),
		k2 = SB_LE32(key[2]),
		k3 = SB_LE32(key[3]);

	ctx->initctx.x[0] = k0;
	ctx->initctx.x[2] = k1;
	ctx->initctx.x[4] = k2;
	ctx->initctx.x[6] = k3;
	ctx->initctx.x[1] = ((k3 << 16) | (k2 >> 16));
	ctx->initctx.x[3] = ((k0 << 16) | (k3 >> 16));
	ctx->initctx.x[5] = ((k1 << 16) | (k0 >> 16));
	ctx->initctx.x[7] = ((k2 << 16) | (k1 >> 16));

	// key expansion
	sb_memdump(ctx->initctx.x, sizeof(ctx->initctx.x));
	//sb_memdump(ctx->initctx.c, sizeof(ctx->initctx.c));
	puts("");

	ctx->initctx.c[0] = SB_ROTL32(k2, 16);
	ctx->initctx.c[2] = SB_ROTL32(k3, 16);
	ctx->initctx.c[4] = SB_ROTL32(k0, 16);
	ctx->initctx.c[6] = SB_ROTL32(k1, 16);
	ctx->initctx.c[1] = ((k0 & 0xFFFF0000) | (k1 & 0x0000FFFF));
	ctx->initctx.c[3] = ((k1 & 0xFFFF0000) | (k2 & 0x0000FFFF));
	ctx->initctx.c[5] = ((k2 & 0xFFFF0000) | (k3 & 0x0000FFFF));
	ctx->initctx.c[7] = ((k3 & 0xFFFF0000) | (k0 & 0x0000FFFF));

	ctx->initctx.carry = 0;

	// key expansion
	//sb_memdump(ctx->initctx.x, sizeof(ctx->initctx.x));
	//sb_memdump(ctx->initctx.c, sizeof(ctx->initctx.c));
	//puts("");

	// 1
	sb_crypto_rabbit_next_state(&ctx->initctx);
	/*sb_memdump(ctx->initctx.x, sizeof(ctx->initctx.x));
	sb_memdump(ctx->initctx.c, sizeof(ctx->initctx.c));
	puts("");*/

	// 2
	sb_crypto_rabbit_next_state(&ctx->initctx);

	// 3
	sb_crypto_rabbit_next_state(&ctx->initctx);

	// 4
	sb_crypto_rabbit_next_state(&ctx->initctx);
	/*sb_memdump(ctx->initctx.x, sizeof(ctx->initctx.x));
	sb_memdump(ctx->initctx.c, sizeof(ctx->initctx.c));
	puts("");*/

	for (i = 8; i--;) {
		ctx->initctx.c[i] ^= ctx->initctx.x[(i + 4) & 7];
	}
	/*sb_memdump(ctx->initctx.x, sizeof(ctx->initctx.x));
	sb_memdump(ctx->initctx.c, sizeof(ctx->initctx.c));
	puts("");*/

	sb_crypto_rabbit_reset(ctx);
}

static void sb_crypto_rabbit_set_iv(sb_crypto_rabbit_ctx_t *ctx, uint64_t iv) {
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

	sb_memdump(key, sizeof(uint32_t) * 4);
	puts("");

	sb_crypto_rabbit_set_key(ctx, key);
	//sb_crypto_rabbit_set_iv(ctx, iv);

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

sb_bool_t sb_crypto_rabbit_process(sb_crypto_rabbit_ctx_t *ctx, void *out, void *in, sb_size_t size) {
	if (!ctx || !out || !in) {
		return sb_false;
	}

	uint32_t *optr = out, *iptr = in;

	for (; size >= 16; size -= 16, optr += 16, iptr += 16) {
		sb_crypto_rabbit_next_state(&ctx->workctx);

		optr[0] = iptr[0] ^ SB_LE32(ctx->workctx.x[0] ^ (ctx->workctx.x[5] >> 16) ^ (ctx->workctx.x[3] << 16));
		optr[1] = iptr[1] ^ SB_LE32(ctx->workctx.x[2] ^ (ctx->workctx.x[7] >> 16) ^ (ctx->workctx.x[5] << 16));
		optr[2] = iptr[2] ^ SB_LE32(ctx->workctx.x[4] ^ (ctx->workctx.x[1] >> 16) ^ (ctx->workctx.x[7] << 16));
		optr[3] = iptr[3] ^ SB_LE32(ctx->workctx.x[6] ^ (ctx->workctx.x[3] >> 16) ^ (ctx->workctx.x[1] << 16));
	}

	if (size) {
		uint32_t b[4];
		uint8_t *bptr = (uint8_t*)b, *obptr = (uint8_t*)optr, *ibptr = (uint8_t*)iptr;
		sb_memset(b, 0, sizeof(b));

		sb_crypto_rabbit_next_state(&ctx->workctx);

		b[0] = SB_LE32(ctx->workctx.x[0] ^ (ctx->workctx.x[5] >> 16) ^ (ctx->workctx.x[3] << 16));
		b[1] = SB_LE32(ctx->workctx.x[2] ^ (ctx->workctx.x[7] >> 16) ^ (ctx->workctx.x[5] << 16));
		b[2] = SB_LE32(ctx->workctx.x[4] ^ (ctx->workctx.x[1] >> 16) ^ (ctx->workctx.x[7] << 16));
		b[3] = SB_LE32(ctx->workctx.x[6] ^ (ctx->workctx.x[3] >> 16) ^ (ctx->workctx.x[1] << 16));

		uint32_t i;
		for (i = size; i--;) {
			obptr[i] = SB_XOR(ibptr[i], bptr[i]);
		}
	}

	return sb_true;
}
