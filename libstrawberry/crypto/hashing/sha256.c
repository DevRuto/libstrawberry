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

#define __FILE_LOCAL__						"crypto/hashing/sha256.c"

#include "./sha256.h"
#include "../../core/error.h"
#include <math.h>

#define ROTR(x, n) ((x >> n) | (x << (32-n)))

IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-08-12");

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

sb_bool_t sb_crypto_sha256_init(sb_crypto_sha256_ctx_t *ctx){
    sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_crypto_sha256_clear(ctx);

	ctx->h0 = 0x6a09e667;
	ctx->h1 = 0xbb67ae85;
	ctx->h2 = 0x3c6ef372;
	ctx->h3 = 0xa54ff53a;
	ctx->h4 = 0x510e527f;
	ctx->h5 = 0x9b05688c;
	ctx->h6 = 0x1f83d9ab;
	ctx->h7 = 0x5be0cd19;

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

sb_bool_t sb_crypto_sha256_update(sb_crypto_sha256_ctx_t *ctx, uint32_t block[16]){
    sb_error_reset();

	if (!ctx) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!block) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;

    sb_size_t i;

    uint32_t w[64];
    sb_memset(w, 0, sizeof(w));
    for (i = 0; i < 16; ++i) {
        w[i] = block[i];
    }

    uint32_t s0, s1, ch, temp1, temp2, maj;
    for (i = 16; i < 64; ++i) {
        s0 = ROTR(w[i-15], 7) ^ ROTR(w[i-15], 18) ^ (w[i-15] >> 3);
        s1 = ROTR(w[i-2], 17) ^ ROTR(w[i-2], 19) ^ (w[i-2] >> 10);
        w[i] = w[i-16] + s0 + w[i-7] + s1;
    }

    // init values
    a = ctx->h0;
    b = ctx->h1;
    c = ctx->h2;
    d = ctx->h3;
    e = ctx->h4;
    f = ctx->h5;
    g = ctx->h6;
    h = ctx->h7;

    // compression
    for (i = 0; i < 64; ++i) {
        s1 = ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25);
        ch = (e & f) ^ (~(e) & g);
        temp1 = h + s1 + ch + constants[i] + w[i];

        s0 = ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22);
        maj = (a & b) ^ (a & c) ^ (b & c);
        temp2 = s0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
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

    int i;
    for (i = 0; i < 4; i++) {
        out[i]      = (ctx->h0 >> (24 - i * 8)) & 0x000000ff;
		out[i + 4]  = (ctx->h1 >> (24 - i * 8)) & 0x000000ff;
		out[i + 8]  = (ctx->h2 >> (24 - i * 8)) & 0x000000ff;
		out[i + 12] = (ctx->h3 >> (24 - i * 8)) & 0x000000ff;
		out[i + 16] = (ctx->h4 >> (24 - i * 8)) & 0x000000ff;
		out[i + 20] = (ctx->h5 >> (24 - i * 8)) & 0x000000ff;
		out[i + 24] = (ctx->h6 >> (24 - i * 8)) & 0x000000ff;
		out[i + 28] = (ctx->h7 >> (24 - i * 8)) & 0x000000ff;
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

    sb_size_t output_size = ((ceil((size+1)/512.0)*512)/8.0);
    uint8_t output[output_size];
    sb_memset(output, 0x00, sizeof(output));
    sb_memcpy(output, in, size);
    output[size] = 128;
    output[output_size-1] = 8*size;
    output[output_size-2] = (8*size) >> 8;
    output[output_size-3] = (8*size) >> 16;
    output[output_size-4] = (8*size) >> 24;

    uint32_t block[16];
    sb_size_t i, j, k = 0;
    for (i = 0; i < (output_size/64); ++i) {
        for (j = 0; j < 16; ++j, k += 4) {
            block[j] = (output[k] << 24) | (output[k+1] << 16) |  (output[k+2] << 8) | (output[k+3]);
        }
        sb_crypto_sha256_update(&ctx, block);
    }

    return sb_crypto_sha256_finish(&ctx, out);
}
