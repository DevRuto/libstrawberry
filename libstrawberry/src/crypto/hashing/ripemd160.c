#include <stdio.h>
#include <stdint.h>
#include "ripemd160.h"
#include "../../core/memory.h"


void sb_crypto_ripemd160_init(uint32_t *buffer) {
	buffer[0] = 0x67452301U;
	buffer[1] = 0xEFCDAB89U;
	buffer[2] = 0x98BADCFEU;
	buffer[3] = 0x10325476U;
	buffer[4] = 0xC3D2E1F0U;
}

void sb_crypto_ripemd160_compress(uint32_t *buffer, uint32_t X[16]) {
	uint32_t A1 = buffer[0], B1 = buffer[1], C1 = buffer[2], D1 = buffer[3], E1 = buffer[4];
	uint32_t A2 = buffer[0], B2 = buffer[1], C2 = buffer[2], D2 = buffer[3], E2 = buffer[4];

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

	D2 += C1 + buffer[1];
	buffer[1] = buffer[2] + D1 + E2;
	buffer[2] = buffer[3] + E1 + A2;
	buffer[3] = buffer[4] + A1 + B2;
	buffer[4] = buffer[0] + B1 + C2;
	buffer[0] = D2;
}

void sb_crypto_ripemd160_finish(uint32_t *buffer, uint8_t *data, size_t lswlen, size_t mswlen) {
	uint32_t x[16];
	sb_memset(x, 0, sizeof(x));

	size_t i;
	for (i = 0; i < (lswlen & 0x3F); ++i) {
		x[i >> 2] ^= ((uint32_t)data[i] << (8 * (i & 3)));
	}

	x[(lswlen >> 2) & 0x0F] ^= (1U << ((8 * (lswlen & 3)) + 7));

	if ((lswlen & 0x3F) > 55) {
		sb_crypto_ripemd160_compress(buffer, x);
		sb_memset(x, 0, sizeof(x));
	}

	x[14] = (uint32_t)(lswlen << 3);
	x[15] = (uint32_t)((lswlen >> 29) | (mswlen << 3));
	sb_crypto_ripemd160_compress(buffer, x);
}

void sb_crypto_ripemd160(uint8_t digest[20], void *data, size_t size) {
	uint32_t block[16];
	sb_memset(&block, 0, sizeof(block));

	uint32_t md[5], ii, *data32 = data;

	sb_crypto_ripemd160_init(md);

	size_t i;
	for (i = size; i > 63; i -= 64) {
		for (ii = 0; ii < 16; ++ii) {
			block[ii] = *data32;
			++data32;
		}
		sb_crypto_ripemd160_compress(md, block);
	}

	sb_crypto_ripemd160_finish(md, data, size, 0);
	for (i = 0; i < 20; i += 4) {
		digest[i    ] = ( md[i >> 2]        & 0xFF);
		digest[i + 1] = ((md[i >> 2] >>  8) & 0xFF);
		digest[i + 2] = ((md[i >> 2] >> 16) & 0xFF);
		digest[i + 3] = ((md[i >> 2] >> 24) & 0xFF);
	}
}

void sb_crypto_ripemd160_str(uint8_t digest_str[41], uint8_t digest[20], sb_bool_t lowercase) {
	uint_fast8_t i;
	uint8_t *buffer = digest_str;
	const char *format = (lowercase ? "%02x" : "%02X");
	for (i = 0; i < 20; ++i) {
		sprintf(buffer, format, digest[i]);
		buffer += 2;
	}
	*buffer = 0;
}
