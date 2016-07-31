#include "../../core/identid.h"
IDENTID("md5.c", "0.1", "1", "2016-07-29");

#include "md5.h"

#include "../../core/error.h"
#include "../../core/memory.h"
#include "../../core/bits.h"


#define F(x, y, z)							((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)							((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)							(((x) ^ (y)) ^ (z))
#define H2(x, y, z)							((x) ^ ((y) ^ (z)))
#define I(x, y, z)							((y) ^ ((x) | ~(z)))

#define MD5R1(a, b, c, d, x, t, s) {		\
	(a) += F((b), (c), (d)) + (x) + (t);	\
	(a) = SB_ROTL32((a), (s));				\
	(a) += (b);								\
}
#define MD5R2(a, b, c, d, x, t, s) {		\
	(a) += G((b), (c), (d)) + (x) + (t);	\
	(a) = SB_ROTL32((a), (s));				\
	(a) += (b);								\
}
#define MD5R3A(a, b, c, d, x, t, s) {		\
	(a) += H((b), (c), (d)) + (x) + (t);	\
	(a) = SB_ROTL32((a), (s));				\
	(a) += (b);								\
}
#define MD5R3B(a, b, c, d, x, t, s) {		\
	(a) += H2((b), (c), (d)) + (x) + (t);	\
	(a) = SB_ROTL32((a), (s));				\
	(a) += (b);								\
}
#define MD5R4(a, b, c, d, x, t, s) {		\
	(a) += I((b), (c), (d)) + (x) + (t);	\
	(a) = SB_ROTL32((a), (s));				\
	(a) += (b);								\
}

#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#define MD5RSET(n) \
	(*(uint32_t*)&ptr[(n) * 4])
#define MD5RGET(n) \
	MD5RSET(n)
#else
#define MD5RSET(n) \
	(ctx->block[(n)] = \
	(uint32_t)ptr[(n) * 4] | \
	((uint32_t)ptr[(n) * 4 + 1] << 8) | \
	((uint32_t)ptr[(n) * 4 + 2] << 16) | \
	((uint32_t)ptr[(n) * 4 + 3] << 24))
#define MD5RGET(n) \
	(ctx->block[(n)])
#endif

static void *sb_crypto_md5_internal_update(sb_crypto_md5_ctx_t *ctx, void *data, size_t size) {
	uint8_t *ptr = data;

	register uint32_t a, b, c, d;
	uint32_t saved_a, saved_b, saved_c, saved_d;

	a = ctx->a;
	b = ctx->b;
	c = ctx->c;
	d = ctx->d;

	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

		MD5R1 (a, b, c, d, MD5RSET( 0), 0xD76AA478,  7);
		MD5R1 (d, a, b, c, MD5RSET( 1), 0xE8C7B756, 12);
		MD5R1 (c, d, a, b, MD5RSET( 2), 0x242070DB, 17);
		MD5R1 (b, c, d, a, MD5RSET( 3), 0xC1BDCEEE, 22);
		MD5R1 (a, b, c, d, MD5RSET( 4), 0xF57C0FAF,  7);
		MD5R1 (d, a, b, c, MD5RSET( 5), 0x4787C62A, 12);
		MD5R1 (c, d, a, b, MD5RSET( 6), 0xA8304613, 17);
		MD5R1 (b, c, d, a, MD5RSET( 7), 0xFD469501, 22);
		MD5R1 (a, b, c, d, MD5RSET( 8), 0x698098D8,  7);
		MD5R1 (d, a, b, c, MD5RSET( 9), 0x8B44F7AF, 12);
		MD5R1 (c, d, a, b, MD5RSET(10), 0xFFFF5BB1, 17);
		MD5R1 (b, c, d, a, MD5RSET(11), 0x895CD7BE, 22);
		MD5R1 (a, b, c, d, MD5RSET(12), 0x6B901122,  7);
		MD5R1 (d, a, b, c, MD5RSET(13), 0xFD987193, 12);
		MD5R1 (c, d, a, b, MD5RSET(14), 0xA679438E, 17);
		MD5R1 (b, c, d, a, MD5RSET(15), 0x49B40821, 22);

		MD5R2 (a, b, c, d, MD5RGET( 1), 0xF61E2562,  5);
		MD5R2 (d, a, b, c, MD5RGET( 6), 0xC040B340,  9);
		MD5R2 (c, d, a, b, MD5RGET(11), 0x265E5A51, 14);
		MD5R2 (b, c, d, a, MD5RGET( 0), 0xE9B6C7AA, 20);
		MD5R2 (a, b, c, d, MD5RGET( 5), 0xD62F105D,  5);
		MD5R2 (d, a, b, c, MD5RGET(10), 0x02441453,  9);
		MD5R2 (c, d, a, b, MD5RGET(15), 0xD8A1E681, 14);
		MD5R2 (b, c, d, a, MD5RGET( 4), 0xE7D3FBC8, 20);
		MD5R2 (a, b, c, d, MD5RGET( 9), 0x21E1CDE6,  5);
		MD5R2 (d, a, b, c, MD5RGET(14), 0xC33707D6,  9);
		MD5R2 (c, d, a, b, MD5RGET( 3), 0xF4D50D87, 14);
		MD5R2 (b, c, d, a, MD5RGET( 8), 0x455A14ED, 20);
		MD5R2 (a, b, c, d, MD5RGET(13), 0xA9E3E905,  5);
		MD5R2 (d, a, b, c, MD5RGET( 2), 0xFCEFA3F8,  9);
		MD5R2 (c, d, a, b, MD5RGET( 7), 0x676F02D9, 14);
		MD5R2 (b, c, d, a, MD5RGET(12), 0x8D2A4C8A, 20);

		MD5R3A(a, b, c, d, MD5RGET( 5), 0xFFFA3942,  4);
		MD5R3B(d, a, b, c, MD5RGET( 8), 0x8771F681, 11);
		MD5R3A(c, d, a, b, MD5RGET(11), 0x6D9D6122, 16);
		MD5R3B(b, c, d, a, MD5RGET(14), 0xFDE5380C, 23);
		MD5R3A(a, b, c, d, MD5RGET( 1), 0xA4BEEA44,  4);
		MD5R3B(d, a, b, c, MD5RGET( 4), 0x4BDECFA9, 11);
		MD5R3A(c, d, a, b, MD5RGET( 7), 0xF6BB4B60, 16);
		MD5R3B(b, c, d, a, MD5RGET(10), 0xBEBFBC70, 23);
		MD5R3A(a, b, c, d, MD5RGET(13), 0x289B7EC6,  4);
		MD5R3B(d, a, b, c, MD5RGET( 0), 0xEAA127FA, 11);
		MD5R3A(c, d, a, b, MD5RGET( 3), 0xD4EF3085, 16);
		MD5R3B(b, c, d, a, MD5RGET( 6), 0x04881D05, 23);
		MD5R3A(a, b, c, d, MD5RGET( 9), 0xD9D4D039,  4);
		MD5R3B(d, a, b, c, MD5RGET(12), 0xE6DB99E5, 11);
		MD5R3A(c, d, a, b, MD5RGET(15), 0x1FA27CF8, 16);
		MD5R3B(b, c, d, a, MD5RGET( 2), 0xC4AC5665, 23);

		MD5R4 (a, b, c, d, MD5RGET( 0), 0xF4292244,  6);
		MD5R4 (d, a, b, c, MD5RGET( 7), 0x432AFF97, 10);
		MD5R4 (c, d, a, b, MD5RGET(14), 0xAB9423A7, 15);
		MD5R4 (b, c, d, a, MD5RGET( 5), 0xFC93A039, 21);
		MD5R4 (a, b, c, d, MD5RGET(12), 0x655B59C3,  6);
		MD5R4 (d, a, b, c, MD5RGET( 3), 0x8F0CCC92, 10);
		MD5R4 (c, d, a, b, MD5RGET(10), 0xFFEFF47D, 15);
		MD5R4 (b, c, d, a, MD5RGET( 1), 0x85845DD1, 21);
		MD5R4 (a, b, c, d, MD5RGET( 8), 0x6FA87E4F,  6);
		MD5R4 (d, a, b, c, MD5RGET(15), 0xFE2CE6E0, 10);
		MD5R4 (c, d, a, b, MD5RGET( 6), 0xA3014314, 15);
		MD5R4 (b, c, d, a, MD5RGET(13), 0x4E0811A1, 21);
		MD5R4 (a, b, c, d, MD5RGET( 4), 0xF7537E82,  6);
		MD5R4 (d, a, b, c, MD5RGET(11), 0xBD3AF235, 10);
		MD5R4 (c, d, a, b, MD5RGET( 2), 0x2AD7D2BB, 15);
		MD5R4 (b, c, d, a, MD5RGET( 9), 0xEB86D391, 21);

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;

		ptr += 64;
	} while (size -= 64);

	ctx->a = a;
	ctx->b = b;
	ctx->c = c;
	ctx->d = d;

	return ptr;
}

void sb_crypto_md5_init(sb_crypto_md5_ctx_t *ctx) {
	sb_error_reset();
	
	if (!ctx) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	sb_crypto_md5_clear(ctx);

	ctx->a = 0x67452301;
	ctx->b = 0xEFCDAB89;
	ctx->c = 0x98BADCFE;
	ctx->d = 0x10325476;
}

void sb_crypto_md5_clear(sb_crypto_md5_ctx_t *ctx) {
	sb_memset(ctx, 0, sizeof(*ctx));
}

void sb_crypto_md5_update(sb_crypto_md5_ctx_t *ctx, void *in, size_t size) {
	sb_error_reset();

	if (!ctx || !in) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	uint32_t saved_lo;
	size_t used, available;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1FFFFFFF) < saved_lo)
		++ctx->hi;
	ctx->hi += (uint32_t)(size >> 29);

	used = saved_lo & 0x3F;

	if (used) {
		available = 64 - used;

		if (size < available) {
			sb_memcpy(&ctx->buffer[used], in, size);
			return;
		}

		sb_memcpy(&ctx->buffer[used], in, available);
		in = (unsigned char *)in + available;
		size -= available;
		sb_crypto_md5_internal_update(ctx, ctx->buffer, 64);
	}

	if (size >= 64) {
		in = sb_crypto_md5_internal_update(ctx, in, size & ~(size_t)0x3F);
		size &= 0x3F;
	}

	sb_memcpy(ctx->buffer, in, size);
}

void sb_crypto_md5_finish(sb_crypto_md5_ctx_t *ctx, void *out) {
	sb_error_reset();
	
	if (!ctx || !out) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return;
	}

	size_t used, available;

	used = ctx->lo & 0x3F;

	ctx->buffer[used++] = 0x80;

	available = 64 - used;

	if (available < 8) {
		sb_memset(&ctx->buffer[used], 0, available);
		sb_crypto_md5_internal_update(ctx, ctx->buffer, 64);
		used = 0;
		available = 64;
	}

	sb_memset(&ctx->buffer[used], 0, available - 8);

	ctx->lo <<= 3;
	*(uint32_t*)(&ctx->buffer[56]) = SB_LE32(ctx->lo);
	*(uint32_t*)(&ctx->buffer[60]) = SB_LE32(ctx->hi);

	sb_crypto_md5_internal_update(ctx, ctx->buffer, 64);

	uint32_t *out32 = out;
	out32[0] = SB_LE32(ctx->a);
	out32[1] = SB_LE32(ctx->b);
	out32[2] = SB_LE32(ctx->c);
	out32[3] = SB_LE32(ctx->d);

	sb_memset(ctx, 0, sizeof(*ctx));
}

void sb_crypto_md5(void *out, void *in, size_t size) {
	sb_crypto_md5_ctx_t ctx;
	sb_crypto_md5_init(&ctx);
	sb_crypto_md5_update(&ctx, in, size);
	sb_crypto_md5_finish(&ctx, out);
	sb_crypto_md5_clear(&ctx);
}