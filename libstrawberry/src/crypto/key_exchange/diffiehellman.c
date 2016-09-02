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

#if !defined(SB_EXCLUDE_CRYPTO_KEY_EXCHANGE_DIFFIEHELLMAN) && defined(HAVE_GMP)


#include "../../core/identid.h"
IDENTID("diffiehellman.c", "0.1", "1", "2016-09-01");

#include "diffiehellman.h"
#include "../../core/error.h"


static void sb_crypto_diffiehellman_perform(mpz_t out, mpz_t x, mpz_t y, mpz_t m) {
	if (mpz_cmp_ui(y, 1UL) == 0) {
		mpz_mod(out, x, m);
		return;
	}

	sb_bool_t even = mpz_even_p(y);

	mpz_t d;
	mpz_init(d);

	if (even) {
		mpz_sub_ui(d, y, 1UL);
	}

	mpz_mdiv_ui(d, y, 2UL);

	sb_crypto_diffiehellman_perform(out, x, d, m);

	mpz_mul(d, out, out);
	mpz_mod(out, d, m);

	if (!even) {
		mpz_mul(d, out, x);
		mpz_mod(out, d, m);
	}

	mpz_clear(d);
}


sb_bool_t sb_crypto_diffiehellman_init(sb_crypto_diffiehellman_ctx_t *ctx, uint16_t bits, uint64_t seed) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	mpz_init(ctx->g);
	mpz_init(ctx->m);
	mpz_init(ctx->pr);
	mpz_init(ctx->pu);
	mpz_init(ctx->s);

	gmp_randinit_mt(ctx->rand);
	if (seed != 0) {
		gmp_randseed_ui(ctx->rand, seed);
	}

	ctx->bits = (bits ? bits : SB_CRYPTO_DIFFIEHELLMAN_DEFAULT_BITCOUNT);

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_clear(sb_crypto_diffiehellman_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	mpz_clear(ctx->g);
	mpz_clear(ctx->m);
	mpz_clear(ctx->pr);
	mpz_clear(ctx->pu);
	mpz_clear(ctx->s);

	gmp_randclear(ctx->rand);

	ctx->bits = 0;

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_generate_base(sb_crypto_diffiehellman_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	mpz_urandomb(ctx->g, ctx->rand, ctx->bits);
	mpz_nextprime(ctx->g, ctx->g);

	mpz_urandomb(ctx->m, ctx->rand, ctx->bits);
	mpz_nextprime(ctx->m, ctx->m);

	if (mpz_cmp(ctx->g, ctx->m) > 0) {
		mpz_swap(ctx->g, ctx->m);
	}

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_generate_keys(sb_crypto_diffiehellman_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	mpz_urandomb(ctx->pr, ctx->rand, ctx->bits);

	sb_crypto_diffiehellman_perform(ctx->pu, ctx->g, ctx->pr, ctx->m);

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_generate(sb_crypto_diffiehellman_ctx_t *ctx) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_crypto_diffiehellman_generate_base(ctx);
	sb_crypto_diffiehellman_generate_keys(ctx);

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_generate_secret(sb_crypto_diffiehellman_ctx_t *ctx, mpz_t public) {
	sb_error_reset();

	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_crypto_diffiehellman_perform(ctx->s, public, ctx->pr, ctx->m);

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_copy_base(sb_crypto_diffiehellman_ctx_t *dst, sb_crypto_diffiehellman_ctx_t *src) {
	sb_error_reset();

	if (!dst) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}
	if (!src) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	mpz_set(dst->g, src->g);
	mpz_set(dst->m, src->m);

	return sb_true;
}


sb_bool_t sb_crypto_diffiehellman_copy_keys(sb_crypto_diffiehellman_ctx_t *dst, sb_crypto_diffiehellman_ctx_t *src) {
	sb_error_reset();

	if (!dst) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}
	if (!src) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	mpz_set(dst->pu, src->pu);
	mpz_set(dst->pr, src->pr);

	return sb_true;
}


#else
#	error crypto/key_exchange/diffiehellman.c requires libgmp
#endif
