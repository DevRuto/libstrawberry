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
**    Contributed by nullruto.
**
*/

#define __FILE_LOCAL__						"crypto/hashing/sha256.c"

#include "./sha256.h"

#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"
#include "../../core/math.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-10-05");


static uint32_t constants[] = {
	0x428A2F98U, 0x71374491U, 0xB5C0FBCFU, 0xE9B5DBA5U,
	0x3956C25BU, 0x59F111F1U, 0x923F82A4U, 0xAB1C5ED5U,
	0xD807AA98U, 0x12835B01U, 0x243185BEU, 0x550C7DC3U,
	0x72BE5D74U, 0x80DEB1FEU, 0x9BDC06A7U, 0xC19BF174U,
	0xE49B69C1U, 0xEFBE4786U, 0x0FC19DC6U, 0x240CA1CCU,
	0x2DE92C6FU, 0x4A7484AAU, 0x5CB0A9DCU, 0x76F988DAU,
	0x983E5152U, 0xA831C66DU, 0xB00327C8U, 0xBF597FC7U,
	0xC6E00BF3U, 0xD5A79147U, 0x06CA6351U, 0x14292967U,
	0x27B70A85U, 0x2E1B2138U, 0x4D2C6DFCU, 0x53380D13U,
	0x650A7354U, 0x766A0ABBU, 0x81C2C92EU, 0x92722C85U,
	0xA2BFE8A1U, 0xA81A664BU, 0xC24B8B70U, 0xC76C51A3U,
	0xD192E819U, 0xD6990624U, 0xF40E3585U, 0x106AA070U,
	0x19A4C116U, 0x1E376C08U, 0x2748774CU, 0x34B0BCB5U,
	0x391C0CB3U, 0x4ED8AA4AU, 0x5B9CCA4FU, 0x682E6FF3U,
	0x748F82EEU, 0x78A5636FU, 0x84C87814U, 0x8CC70208U,
	0x90BEFFFAU, 0xA4506CEBU, 0xBEF9A3F7U, 0xC67178F2U
};


sb_bool_t sb_crypto_sha256_init(sb_crypto_sha256_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_crypto_sha256_clear(ctx);

	ctx->h0 = 0x6A09E667U;
	ctx->h1 = 0xBB67AE85U;
	ctx->h2 = 0x3C6EF372U;
	ctx->h3 = 0xA54FF53AU;
	ctx->h4 = 0x510E527FU;
	ctx->h5 = 0x9B05688CU;
	ctx->h6 = 0x1F83D9ABU;
	ctx->h7 = 0x5BE0CD19U;

	return sb_true;
}


sb_bool_t sb_crypto_sha256_clear(sb_crypto_sha256_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_memset(ctx, 0, sizeof(*ctx));

	return sb_true;
}


sb_bool_t sb_crypto_sha256_update(sb_crypto_sha256_ctx_t *ctx, uint32_t block[16]) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!block) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	register uint32_t
		a = ctx->h0,
		b = ctx->h1,
		c = ctx->h2,
		d = ctx->h3,
		e = ctx->h4,
		f = ctx->h5,
		g = ctx->h6,
		h = ctx->h7,
		s0, s1, ch, temp1, temp2, maj;

	uint32_t w[64];

	register sb_size_t i;

	for (i = 16; i--;) {
		w[i] = block[i];
	}

	for (i = 16; i < 64; ++i) {
		s0 = SB_ROTR32(w[(i - 15)],  7) ^ SB_ROTR32(w[(i - 15)], 18) ^ (w[(i - 15)] >>  3);
		s1 = SB_ROTR32(w[(i -  2)], 17) ^ SB_ROTR32(w[(i -  2)], 19) ^ (w[(i -  2)] >> 10);
		w[i] = w[(i - 16)] + s0 + w[(i - 7)] + s1;
	}

	// compression
	for (i = 0; i < 64; ++i) {
		s1 = (SB_ROTR32(e, 6) ^ SB_ROTR32(e, 11) ^ SB_ROTR32(e, 25));
		ch = ((e & f) ^ (~(e) & g));
		temp1 = (h + s1 + ch + constants[i] + w[i]);

		s0 = (SB_ROTR32(a, 2) ^ SB_ROTR32(a, 13) ^ SB_ROTR32(a, 22));
		maj = ((a & b) ^ (a & c) ^ (b & c));
		temp2 = (s0 + maj);

		h = g;
		g = f;
		f = e;
		e = (d + temp1);
		d = c;
		c = b;
		b = a;
		a = (temp1 + temp2);
	}

	ctx->h0 += a;
	ctx->h1 += b;
	ctx->h2 += c;
	ctx->h3 += d;
	ctx->h4 += e;
	ctx->h5 += f;
	ctx->h6 += g;
	ctx->h7 += h;

	return sb_true;
}


sb_bool_t sb_crypto_sha256_finish(sb_crypto_sha256_ctx_t *ctx, uint8_t out[32]) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	uint_fast8_t i;
	for (i = 4; i--;) {
		out[i     ] = (ctx->h0 >> (24 - (8 * i))) & 0xFF;
		out[i +  4] = (ctx->h1 >> (24 - (8 * i))) & 0xFF;
		out[i +  8] = (ctx->h2 >> (24 - (8 * i))) & 0xFF;
		out[i + 12] = (ctx->h3 >> (24 - (8 * i))) & 0xFF;
		out[i + 16] = (ctx->h4 >> (24 - (8 * i))) & 0xFF;
		out[i + 20] = (ctx->h5 >> (24 - (8 * i))) & 0xFF;
		out[i + 24] = (ctx->h6 >> (24 - (8 * i))) & 0xFF;
		out[i + 28] = (ctx->h7 >> (24 - (8 * i))) & 0xFF;
	}

	return sb_true;
}


sb_bool_t sb_crypto_sha256(uint8_t out[32], void *in, sb_size_t size) {
	sb_error_reset();

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!in) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	sb_crypto_sha256_ctx_t ctx;
	sb_crypto_sha256_init(&ctx);

	sb_size_t size_rounded = sb_math_round_block(64, (size + 1));

	uint8_t output[size_rounded];
	sb_memcpy(output, in, size);
	sb_memset((output + size), 0, size_rounded - size);

	output[size] = 0x80;
	output[size_rounded - 1] =  (8 * size);
	output[size_rounded - 2] = ((8 * size) >>  8);
	output[size_rounded - 3] = ((8 * size) >> 16);
	output[size_rounded - 4] = ((8 * size) >> 24);

	uint32_t block[16], *in32 = (uint32_t*)output;
	sb_size_t i, j;
	for (i = (size_rounded / 64); i--;) {
		for (j = 0; j < 16; ++j) {
			block[j] = SB_BE32(*in32);
			++in32;
		}
		sb_crypto_sha256_update(&ctx, block);
	}

	sb_bool_t valid = sb_crypto_sha256_finish(&ctx, out);

	sb_crypto_sha256_clear(&ctx);

	return valid;
}
