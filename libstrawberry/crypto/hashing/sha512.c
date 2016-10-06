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

#define __FILE_LOCAL__						"crypto/hashing/sha512.c"

#if !defined(SB_EXCLUDE_CRYPTO_HASHING) && !defined(SB_EXCLUDE_CRYPTO_HASHING_SHA512)

#define SB_INTRINSICS

#include "./sha512.h"

#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"
#include "../../core/math.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-10-06");


static uint64_t constants[] = {
	0x428A2F98D728AE22U, 0x7137449123EF65CDU, 0xB5C0FBCFEC4D3B2FU, 0xE9B5DBA58189DBBCU,
	0x3956C25BF348B538U, 0x59F111F1B605D019U, 0x923F82A4AF194F9BU, 0xAB1C5ED5DA6D8118U,
	0xD807AA98A3030242U, 0x12835B0145706FBEU, 0x243185BE4EE4B28CU, 0x550C7DC3D5FFB4E2U,
	0x72BE5D74F27B896FU, 0x80DEB1FE3B1696B1U, 0x9BDC06A725C71235U, 0xC19BF174CF692694U,
	0xE49B69C19EF14AD2U, 0xEFBE4786384F25E3U, 0x0FC19DC68B8CD5B5U, 0x240CA1CC77AC9C65U,
	0x2DE92C6F592B0275U, 0x4A7484AA6EA6E483U, 0x5CB0A9DCBD41FBD4U, 0x76F988DA831153B5U,
	0x983E5152EE66DFABU, 0xA831C66D2DB43210U, 0xB00327C898FB213FU, 0xBF597FC7BEEF0EE4U,
	0xC6E00BF33DA88FC2U, 0xD5A79147930AA725U, 0x06CA6351E003826FU, 0x142929670A0E6E70U,
	0x27B70A8546D22FFCU, 0x2E1B21385C26C926U, 0x4D2C6DFC5AC42AEDU, 0x53380D139D95B3DFU,
	0x650A73548BAF63DEU, 0x766A0ABB3C77B2A8U, 0x81C2C92E47EDAEE6U, 0x92722C851482353BU,
	0xA2BFE8A14CF10364U, 0xA81A664BBC423001U, 0xC24B8B70D0F89791U, 0xC76C51A30654BE30U,
	0xD192E819D6EF5218U, 0xD69906245565A910U, 0xF40E35855771202AU, 0x106AA07032BBD1B8U,
	0x19A4C116B8D2D0C8U, 0x1E376C085141AB53U, 0x2748774CDF8EEB99U, 0x34B0BCB5E19B48A8U,
	0x391C0CB3C5C95A63U, 0x4ED8AA4AE3418ACBU, 0x5B9CCA4F7763E373U, 0x682E6FF3D6B2B8A3U,
	0x748F82EE5DEFB2FCU, 0x78A5636F43172F60U, 0x84C87814A1F0AB72U, 0x8CC702081A6439ECU,
	0x90BEFFFA23631E28U, 0xA4506CEBDE82BDE9U, 0xBEF9A3F7B2C67915U, 0xC67178F2E372532BU,
	0xCA273ECEEA26619CU, 0xD186B8C721C0C207U, 0xEADA7DD6CDE0EB1EU, 0xF57D4F7FEE6ED178U,
	0x06F067AA72176FBAU, 0x0A637DC5A2C898A6U, 0x113F9804BEF90DAEU, 0x1B710B35131C471BU,
	0x28DB77F523047D84U, 0x32CAAB7B40C72493U, 0x3C9EBE0A15C9BEBCU, 0x431D67C49C100D4CU,
	0x4CC5D4BECB3E42B6U, 0x597F299CFC657E2AU, 0x5FCB6FAB3AD6FAECU, 0x6C44198C4A475817U
};


sb_bool_t sb_crypto_sha512_init(sb_crypto_sha512_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_crypto_sha512_clear(ctx);

	ctx->h0 = 0x6A09E667F3BCC908U;
	ctx->h1 = 0xBB67AE8584CAA73BU;
	ctx->h2 = 0x3C6EF372FE94F82BU;
	ctx->h3 = 0xA54FF53A5F1D36F1U;
	ctx->h4 = 0x510E527FADE682D1U;
	ctx->h5 = 0x9B05688C2B3E6C1FU;
	ctx->h6 = 0x1F83D9ABFB41BD6BU;
	ctx->h7 = 0x5BE0CD19137E2179U;

	return sb_true;
}


sb_bool_t sb_crypto_sha512_clear(sb_crypto_sha512_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_memset(ctx, 0, sizeof(*ctx));

	return sb_true;
}


sb_bool_t sb_crypto_sha512_update(sb_crypto_sha512_ctx_t *ctx, uint64_t block[16]) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!block) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	register uint64_t
			a = ctx->h0,
			b = ctx->h1,
			c = ctx->h2,
			d = ctx->h3,
			e = ctx->h4,
			f = ctx->h5,
			g = ctx->h6,
			h = ctx->h7,
			s0, s1, ch, temp1, temp2, maj;

	uint64_t w[80];

	register size_t i;
	for (i = 16; i--;) {
		w[i] = block[i];
	}

	for (i = 16; i < 80; ++i) {
		s0 = SB_ROTR64(w[i-15], 1) ^ SB_ROTR64(w[i-15], 8) ^ (w[i-15] >> 7);
		s1 = SB_ROTR64(w[i-2], 19) ^ SB_ROTR64(w[i-2], 61) ^ (w[i-2] >> 6);
		w[i] = w[i-16] + s0 + w[i-7] + s1;
	}

	// compression
	for (i = 0; i < 80; ++i) {
		s1 = SB_ROTR64(e, 14) ^ SB_ROTR64(e, 18) ^ SB_ROTR64(e, 41);
		ch = (e & f) ^ (~(e) & g);
		temp1 = h + s1 + ch + constants[i] + w[i];
		s0 = SB_ROTR64(a, 28) ^ SB_ROTR64(a, 34) ^ SB_ROTR64(a, 39);
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


sb_bool_t sb_crypto_sha512_finish(sb_crypto_sha512_ctx_t *ctx, uint8_t out[64]) {
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
	for (i = 8; i--;) {
		out[i     ] = ((ctx->h0 >> (56 - (8 * i))) & 0xFF);
		out[i +  8] = ((ctx->h1 >> (56 - (8 * i))) & 0xFF);
		out[i + 16] = ((ctx->h2 >> (56 - (8 * i))) & 0xFF);
		out[i + 24] = ((ctx->h3 >> (56 - (8 * i))) & 0xFF);
		out[i + 32] = ((ctx->h4 >> (56 - (8 * i))) & 0xFF);
		out[i + 40] = ((ctx->h5 >> (56 - (8 * i))) & 0xFF);
		out[i + 48] = ((ctx->h6 >> (56 - (8 * i))) & 0xFF);
		out[i + 56] = ((ctx->h7 >> (56 - (8 * i))) & 0xFF);
	}

	return sb_true;
}


sb_bool_t sb_crypto_sha512(uint8_t out[64], void *in, sb_size_t size) {
	sb_error_reset();

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!in) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	sb_crypto_sha512_ctx_t ctx;
	sb_crypto_sha512_init(&ctx);

	sb_size_t buffer_size = sb_math_round_block(128, (size + 1));

	SB_MEM_BUFFER_ALLOC(uint8_t, buffer, buffer_size);

	sb_memcpy(buffer, in, size);
	sb_memset((buffer + size), 0, buffer_size - size);

	buffer[size] = 0x80;

	buffer[buffer_size - 1] = ( (8 * size)        & 0xFF);
	buffer[buffer_size - 2] = (((8 * size) >>  8) & 0xFF);
	buffer[buffer_size - 3] = (((8 * size) >> 16) & 0xFF);
	buffer[buffer_size - 4] = (((8 * size) >> 24) & 0xFF);

	uint64_t block[16], *in64 = (uint64_t*)buffer;

	sb_size_t i, j;
	for (i = (buffer_size)/128; i--;) {
		for (j = 0; j < 16; ++j) {
			block[j] = SB_BE64(*in64);
			++in64;
		}
		sb_crypto_sha512_update(&ctx, block);
	}

	SB_MEM_BUFFER_FREE(buffer);

	sb_bool_t valid = sb_crypto_sha512_finish(&ctx, out);

	sb_crypto_sha512_clear(&ctx);

	return valid;
}

#else
#	ifdef REPORT_EXCLUSION
#		pragma message("Excluded: "__FILE_LOCAL__)
#	endif
#endif
