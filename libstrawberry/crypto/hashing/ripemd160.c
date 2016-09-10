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

#define __FILE_LOCAL__						"crypto/hashing/ripemd160.c"

#include "ripemd160.h"

#include "../../core/memory.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-07-29");


#define R1(x, y, z)							((x) ^ (y) ^ (z))
#define R2(x, y, z)							(((x) & (y)) | (~(x) & (z)))
#define R3(x, y, z)							(((x) | ~(y)) ^ (z))
#define R4(x, y, z)							(((x) & (z)) | ((y) & ~(z)))
#define R5(x, y, z)							((x) ^ ((y) | ~(z)))

#define NR1(a,b,c,d,e,x,s)					{ (a) += R1((b), (c), (d)) + (x);               (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR2(a,b,c,d,e,x,s)					{ (a) += R2((b), (c), (d)) + (x) + 0x5A827999U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR3(a,b,c,d,e,x,s)					{ (a) += R3((b), (c), (d)) + (x) + 0x6ED9EBA1U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR4(a,b,c,d,e,x,s)					{ (a) += R4((b), (c), (d)) + (x) + 0x8F1BBCDCU; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR5(a,b,c,d,e,x,s)					{ (a) += R5((b), (c), (d)) + (x) + 0xA953FD4EU; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }

#define PR1(a,b,c,d,e,x,s)					{ (a) += R5((b), (c), (d)) + (x) + 0x50A28BE6U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR2(a,b,c,d,e,x,s)					{ (a) += R4((b), (c), (d)) + (x) + 0x5C4DD124U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR3(a,b,c,d,e,x,s)					{ (a) += R3((b), (c), (d)) + (x) + 0x6D703EF3U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR4(a,b,c,d,e,x,s)					{ (a) += R2((b), (c), (d)) + (x) + 0x7A6D76E9U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR5(a,b,c,d,e,x,s)					{ (a) += R1((b), (c), (d)) + (x);               (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }


void sb_crypto_ripemd160_init(sb_crypto_ripemd160_ctx_t *ctx) {
	ctx->data[0] = 0x67452301U;
	ctx->data[1] = 0xEFCDAB89U;
	ctx->data[2] = 0x98BADCFEU;
	ctx->data[3] = 0x10325476U;
	ctx->data[4] = 0xC3D2E1F0U;
}


void sb_crypto_ripemd160_clear(sb_crypto_ripemd160_ctx_t *ctx) {
	sb_memset(ctx, 0, sizeof(*ctx));
}


void sb_crypto_ripemd160_update(sb_crypto_ripemd160_ctx_t *ctx, uint32_t X[16]) {
	register uint32_t A1 = ctx->data[0], B1 = ctx->data[1], C1 = ctx->data[2], D1 = ctx->data[3], E1 = ctx->data[4];
	register uint32_t A2 = ctx->data[0], B2 = ctx->data[1], C2 = ctx->data[2], D2 = ctx->data[3], E2 = ctx->data[4];

	NR1(A1, B1, C1, D1, E1, X[ 0], 11);
	NR1(E1, A1, B1, C1, D1, X[ 1], 14);
	NR1(D1, E1, A1, B1, C1, X[ 2], 15);
	NR1(C1, D1, E1, A1, B1, X[ 3], 12);
	NR1(B1, C1, D1, E1, A1, X[ 4],  5);
	NR1(A1, B1, C1, D1, E1, X[ 5],  8);
	NR1(E1, A1, B1, C1, D1, X[ 6],  7);
	NR1(D1, E1, A1, B1, C1, X[ 7],  9);
	NR1(C1, D1, E1, A1, B1, X[ 8], 11);
	NR1(B1, C1, D1, E1, A1, X[ 9], 13);
	NR1(A1, B1, C1, D1, E1, X[10], 14);
	NR1(E1, A1, B1, C1, D1, X[11], 15);
	NR1(D1, E1, A1, B1, C1, X[12],  6);
	NR1(C1, D1, E1, A1, B1, X[13],  7);
	NR1(B1, C1, D1, E1, A1, X[14],  9);
	NR1(A1, B1, C1, D1, E1, X[15],  8);

	NR2(E1, A1, B1, C1, D1, X[ 7],  7);
	NR2(D1, E1, A1, B1, C1, X[ 4],  6);
	NR2(C1, D1, E1, A1, B1, X[13],  8);
	NR2(B1, C1, D1, E1, A1, X[ 1], 13);
	NR2(A1, B1, C1, D1, E1, X[10], 11);
	NR2(E1, A1, B1, C1, D1, X[ 6],  9);
	NR2(D1, E1, A1, B1, C1, X[15],  7);
	NR2(C1, D1, E1, A1, B1, X[ 3], 15);
	NR2(B1, C1, D1, E1, A1, X[12],  7);
	NR2(A1, B1, C1, D1, E1, X[ 0], 12);
	NR2(E1, A1, B1, C1, D1, X[ 9], 15);
	NR2(D1, E1, A1, B1, C1, X[ 5],  9);
	NR2(C1, D1, E1, A1, B1, X[ 2], 11);
	NR2(B1, C1, D1, E1, A1, X[14],  7);
	NR2(A1, B1, C1, D1, E1, X[11], 13);
	NR2(E1, A1, B1, C1, D1, X[ 8], 12);

	NR3(D1, E1, A1, B1, C1, X[ 3], 11);
	NR3(C1, D1, E1, A1, B1, X[10], 13);
	NR3(B1, C1, D1, E1, A1, X[14],  6);
	NR3(A1, B1, C1, D1, E1, X[ 4],  7);
	NR3(E1, A1, B1, C1, D1, X[ 9], 14);
	NR3(D1, E1, A1, B1, C1, X[15],  9);
	NR3(C1, D1, E1, A1, B1, X[ 8], 13);
	NR3(B1, C1, D1, E1, A1, X[ 1], 15);
	NR3(A1, B1, C1, D1, E1, X[ 2], 14);
	NR3(E1, A1, B1, C1, D1, X[ 7],  8);
	NR3(D1, E1, A1, B1, C1, X[ 0], 13);
	NR3(C1, D1, E1, A1, B1, X[ 6],  6);
	NR3(B1, C1, D1, E1, A1, X[13],  5);
	NR3(A1, B1, C1, D1, E1, X[11], 12);
	NR3(E1, A1, B1, C1, D1, X[ 5],  7);
	NR3(D1, E1, A1, B1, C1, X[12],  5);

	NR4(C1, D1, E1, A1, B1, X[ 1], 11);
	NR4(B1, C1, D1, E1, A1, X[ 9], 12);
	NR4(A1, B1, C1, D1, E1, X[11], 14);
	NR4(E1, A1, B1, C1, D1, X[10], 15);
	NR4(D1, E1, A1, B1, C1, X[ 0], 14);
	NR4(C1, D1, E1, A1, B1, X[ 8], 15);
	NR4(B1, C1, D1, E1, A1, X[12],  9);
	NR4(A1, B1, C1, D1, E1, X[ 4],  8);
	NR4(E1, A1, B1, C1, D1, X[13],  9);
	NR4(D1, E1, A1, B1, C1, X[ 3], 14);
	NR4(C1, D1, E1, A1, B1, X[ 7],  5);
	NR4(B1, C1, D1, E1, A1, X[15],  6);
	NR4(A1, B1, C1, D1, E1, X[14],  8);
	NR4(E1, A1, B1, C1, D1, X[ 5],  6);
	NR4(D1, E1, A1, B1, C1, X[ 6],  5);
	NR4(C1, D1, E1, A1, B1, X[ 2], 12);

	NR5(B1, C1, D1, E1, A1, X[ 4],  9);
	NR5(A1, B1, C1, D1, E1, X[ 0], 15);
	NR5(E1, A1, B1, C1, D1, X[ 5],  5);
	NR5(D1, E1, A1, B1, C1, X[ 9], 11);
	NR5(C1, D1, E1, A1, B1, X[ 7],  6);
	NR5(B1, C1, D1, E1, A1, X[12],  8);
	NR5(A1, B1, C1, D1, E1, X[ 2], 13);
	NR5(E1, A1, B1, C1, D1, X[10], 12);
	NR5(D1, E1, A1, B1, C1, X[14],  5);
	NR5(C1, D1, E1, A1, B1, X[ 1], 12);
	NR5(B1, C1, D1, E1, A1, X[ 3], 13);
	NR5(A1, B1, C1, D1, E1, X[ 8], 14);
	NR5(E1, A1, B1, C1, D1, X[11], 11);
	NR5(D1, E1, A1, B1, C1, X[ 6],  8);
	NR5(C1, D1, E1, A1, B1, X[15],  5);
	NR5(B1, C1, D1, E1, A1, X[13],  6);

	PR1(A2, B2, C2, D2, E2, X[ 5],  8);
	PR1(E2, A2, B2, C2, D2, X[14],  9);
	PR1(D2, E2, A2, B2, C2, X[ 7],  9);
	PR1(C2, D2, E2, A2, B2, X[ 0], 11);
	PR1(B2, C2, D2, E2, A2, X[ 9], 13);
	PR1(A2, B2, C2, D2, E2, X[ 2], 15);
	PR1(E2, A2, B2, C2, D2, X[11], 15);
	PR1(D2, E2, A2, B2, C2, X[ 4],  5);
	PR1(C2, D2, E2, A2, B2, X[13],  7);
	PR1(B2, C2, D2, E2, A2, X[ 6],  7);
	PR1(A2, B2, C2, D2, E2, X[15],  8);
	PR1(E2, A2, B2, C2, D2, X[ 8], 11);
	PR1(D2, E2, A2, B2, C2, X[ 1], 14);
	PR1(C2, D2, E2, A2, B2, X[10], 14);
	PR1(B2, C2, D2, E2, A2, X[ 3], 12);
	PR1(A2, B2, C2, D2, E2, X[12],  6);

	PR2(E2, A2, B2, C2, D2, X[ 6],  9);
	PR2(D2, E2, A2, B2, C2, X[11], 13);
	PR2(C2, D2, E2, A2, B2, X[ 3], 15);
	PR2(B2, C2, D2, E2, A2, X[ 7],  7);
	PR2(A2, B2, C2, D2, E2, X[ 0], 12);
	PR2(E2, A2, B2, C2, D2, X[13],  8);
	PR2(D2, E2, A2, B2, C2, X[ 5],  9);
	PR2(C2, D2, E2, A2, B2, X[10], 11);
	PR2(B2, C2, D2, E2, A2, X[14],  7);
	PR2(A2, B2, C2, D2, E2, X[15],  7);
	PR2(E2, A2, B2, C2, D2, X[ 8], 12);
	PR2(D2, E2, A2, B2, C2, X[12],  7);
	PR2(C2, D2, E2, A2, B2, X[ 4],  6);
	PR2(B2, C2, D2, E2, A2, X[ 9], 15);
	PR2(A2, B2, C2, D2, E2, X[ 1], 13);
	PR2(E2, A2, B2, C2, D2, X[ 2], 11);

	PR3(D2, E2, A2, B2, C2, X[15],  9);
	PR3(C2, D2, E2, A2, B2, X[ 5],  7);
	PR3(B2, C2, D2, E2, A2, X[ 1], 15);
	PR3(A2, B2, C2, D2, E2, X[ 3], 11);
	PR3(E2, A2, B2, C2, D2, X[ 7],  8);
	PR3(D2, E2, A2, B2, C2, X[14],  6);
	PR3(C2, D2, E2, A2, B2, X[ 6],  6);
	PR3(B2, C2, D2, E2, A2, X[ 9], 14);
	PR3(A2, B2, C2, D2, E2, X[11], 12);
	PR3(E2, A2, B2, C2, D2, X[ 8], 13);
	PR3(D2, E2, A2, B2, C2, X[12],  5);
	PR3(C2, D2, E2, A2, B2, X[ 2], 14);
	PR3(B2, C2, D2, E2, A2, X[10], 13);
	PR3(A2, B2, C2, D2, E2, X[ 0], 13);
	PR3(E2, A2, B2, C2, D2, X[ 4],  7);
	PR3(D2, E2, A2, B2, C2, X[13],  5);

	PR4(C2, D2, E2, A2, B2, X[ 8], 15);
	PR4(B2, C2, D2, E2, A2, X[ 6],  5);
	PR4(A2, B2, C2, D2, E2, X[ 4],  8);
	PR4(E2, A2, B2, C2, D2, X[ 1], 11);
	PR4(D2, E2, A2, B2, C2, X[ 3], 14);
	PR4(C2, D2, E2, A2, B2, X[11], 14);
	PR4(B2, C2, D2, E2, A2, X[15],  6);
	PR4(A2, B2, C2, D2, E2, X[ 0], 14);
	PR4(E2, A2, B2, C2, D2, X[ 5],  6);
	PR4(D2, E2, A2, B2, C2, X[12],  9);
	PR4(C2, D2, E2, A2, B2, X[ 2], 12);
	PR4(B2, C2, D2, E2, A2, X[13],  9);
	PR4(A2, B2, C2, D2, E2, X[ 9], 12);
	PR4(E2, A2, B2, C2, D2, X[ 7],  5);
	PR4(D2, E2, A2, B2, C2, X[10], 15);
	PR4(C2, D2, E2, A2, B2, X[14],  8);

	PR5(B2, C2, D2, E2, A2, X[12],  8);
	PR5(A2, B2, C2, D2, E2, X[15],  5);
	PR5(E2, A2, B2, C2, D2, X[10], 12);
	PR5(D2, E2, A2, B2, C2, X[ 4],  9);
	PR5(C2, D2, E2, A2, B2, X[ 1], 12);
	PR5(B2, C2, D2, E2, A2, X[ 5],  5);
	PR5(A2, B2, C2, D2, E2, X[ 8], 14);
	PR5(E2, A2, B2, C2, D2, X[ 7],  6);
	PR5(D2, E2, A2, B2, C2, X[ 6],  8);
	PR5(C2, D2, E2, A2, B2, X[ 2], 13);
	PR5(B2, C2, D2, E2, A2, X[13],  6);
	PR5(A2, B2, C2, D2, E2, X[14],  5);
	PR5(E2, A2, B2, C2, D2, X[ 0], 15);
	PR5(D2, E2, A2, B2, C2, X[ 3], 13);
	PR5(C2, D2, E2, A2, B2, X[ 9], 11);
	PR5(B2, C2, D2, E2, A2, X[11], 11);

	D2 += C1 + ctx->data[1];
	ctx->data[1] = ctx->data[2] + D1 + E2;
	ctx->data[2] = ctx->data[3] + E1 + A2;
	ctx->data[3] = ctx->data[4] + A1 + B2;
	ctx->data[4] = ctx->data[0] + B1 + C2;
	ctx->data[0] = D2;
}


void sb_crypto_ripemd160_finish(sb_crypto_ripemd160_ctx_t *ctx, void *in, sb_size_t size) {
	uint32_t x[16];
	sb_memset(x, 0, sizeof(x));

	uint8_t *data = in;

	register sb_size_t i;
	for (i = 0; i < (size & 0x3F); ++i) {
		x[i >> 2] ^= ((uint32_t)data[i] << (8 * (i & 3)));
	}

	x[(size >> 2) & 0x0F] ^= (1U << ((8 * (size & 3)) + 7));

	if ((size & 0x3F) > 55) {
		sb_crypto_ripemd160_update(ctx, x);
		sb_memset(x, 0, sizeof(x));
	}

	x[14] = (uint32_t)(size << 3);
	x[15] = (uint32_t)(size >> 29);
	sb_crypto_ripemd160_update(ctx, x);
}


void sb_crypto_ripemd160(uint8_t digest[20], void *data, sb_size_t size) {
	uint32_t block[16];
	sb_memset(&block, 0, sizeof(block));

	sb_crypto_ripemd160_ctx_t ctx;
	uint32_t ii, *data32 = data;

	sb_crypto_ripemd160_init(&ctx);

	register sb_size_t i;
	for (i = size; i > 63; i -= 64) {
		for (ii = 0; ii < 16; ++ii) {
			block[ii] = *data32;
			++data32;
		}
		sb_crypto_ripemd160_update(&ctx, block);
	}

	sb_crypto_ripemd160_finish(&ctx, data, size);

	for (i = 0; i < 20; i += 4) {
		digest[i    ] = ( ctx.data[i >> 2]        & 0xFF);
		digest[i + 1] = ((ctx.data[i >> 2] >>  8) & 0xFF);
		digest[i + 2] = ((ctx.data[i >> 2] >> 16) & 0xFF);
		digest[i + 3] = ((ctx.data[i >> 2] >> 24) & 0xFF);
	}

	sb_crypto_ripemd160_clear(&ctx);
}
