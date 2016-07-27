#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../libstrawberry/src/core/memory.h"
//#include "../../libstrawberry/src/structures/crypto.h"
#include "../../libstrawberry/src/core/bits.h"
#include "../../libstrawberry/src/crypto/hashing/ripemd160.h"
#include "../../libstrawberry/src/crypto/symmetric/rijndael.h"
#include "../../libstrawberry/src//core/time.h"

typedef struct test {
	uint8_t flags;
	/*char bit1 : 1;
	char bit2 : 1;
	char bit3 : 1;
	char bit4 : 1;
	char bit5 : 1;
	char bit6 : 1;
	char bit7 : 1;
	char bit8 : 1;*/
} test_t;

int main(int argc, char **argv, char **env) {
	/*uint8_t digest[20], digest_str[41];

	char *tests[6] = {
		"a",
		"abc",
		"message digest",
		"abcdefghijklmnopqrstuvwxyz",
		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
	};

	uint8_t results[6][20] = { // http://homes.esat.kuleuven.be/~bosselae/ripemd160.html
		{ 0x0B, 0xDC, 0x9D, 0x2D, 0x25, 0x6B, 0x3E, 0xE9, 0xDA, 0xAE, 0x34, 0x7B, 0xE6, 0xF4, 0xDC, 0x83, 0x5A, 0x46, 0x7F, 0xFE },
		{ 0x8E, 0xB2, 0x08, 0xF7, 0xE0, 0x5D, 0x98, 0x7A, 0x9B, 0x04, 0x4A, 0x8E, 0x98, 0xC6, 0xB0, 0x87, 0xF1, 0x5A, 0x0B, 0xFC },
		{ 0x5D, 0x06, 0x89, 0xEF, 0x49, 0xD2, 0xFA, 0xE5, 0x72, 0xB8, 0x81, 0xB1, 0x23, 0xA8, 0x5F, 0xFA, 0x21, 0x59, 0x5F, 0x36 },
		{ 0xF7, 0x1C, 0x27, 0x10, 0x9C, 0x69, 0x2C, 0x1B, 0x56, 0xBB, 0xDC, 0xEB, 0x5B, 0x9D, 0x28, 0x65, 0xB3, 0x70, 0x8D, 0xBC },
		{ 0x12, 0xA0, 0x53, 0x38, 0x4A, 0x9C, 0x0C, 0x88, 0xE4, 0x05, 0xA0, 0x6C, 0x27, 0xDC, 0xF4, 0x9A, 0xDA, 0x62, 0xEB, 0x2B },
		{ 0xB0, 0xE2, 0x0B, 0x6E, 0x31, 0x16, 0x64, 0x02, 0x86, 0xED, 0x3A, 0x87, 0xA5, 0x71, 0x30, 0x79, 0xB2, 0x1F, 0x51, 0x89 }
	};

	uint32_t i;
	for (i = 0; i < 6; ++i) {
		sb_memset(digest, 0, 20);
		sb_crypto_ripemd160(digest, tests[i], strlen(tests[i]));
		sb_crypto_ripemd160_str(digest_str, digest, 1);
		printf("%s\n%s\n", digest_str, tests[i]);
		if (sb_memcmp(digest, results[i], 20)) {
			puts("failed\n");
		} else {
			puts("succeeded\n");
		}
	}*/

	/*const char key[32] = { 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF };
	const char blk[16] = { 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF };
	char out[20], str[41];
	sb_memset(out, 0, 20);

	sb_crypto_rijndael_t rijndael;

	uint8_t i;
	for (i = 0; i < 10; ++i) {
		sb_memset(key, i, 32);
		sb_memset(blk, i, 16);
		sb_crypto_rijndael_init(&rijndael, 3, &key);
		sb_crypto_rijndael_encrypt_block(&rijndael, out, blk);
		sb_crypto_ripemd160_str(str, out, 0);
		printf("%02X %s\n", i, str);
		sb_crypto_rijndael_decrypt_block(&rijndael, blk, out);
		sb_crypto_ripemd160_str(str, blk, 0);
		printf("   %s\n", str);
		sb_crypto_rijndael_clear(&rijndael);
	}*/

	test_t test;
	sb_memset(&test, 0, sizeof(test));

	unsigned long long iter, ns_start = sb_time_nsec(), ns_stop = 0;
	for (iter = 0; iter < 50000000; ++iter) {
		/*if (test.bit1) {
			test.bit1 = 0;
		} else {
			test.bit1 = 1;
		}
		if (test.bit2) {
			test.bit2 = 0;
		} else {
			test.bit2 = 1;
		}
		if (test.bit3) {
			test.bit3 = 0;
		} else {
			test.bit3 = 1;
		}
		if (test.bit4) {
			test.bit4 = 0;
		} else {
			test.bit4 = 1;
		}
		if (test.bit5) {
			test.bit5 = 0;
		} else {
			test.bit5 = 1;
		}
		if (test.bit6) {
			test.bit6 = 0;
		} else {
			test.bit6 = 1;
		}
		if (test.bit7) {
			test.bit7 = 0;
		} else {
			test.bit7 = 1;
		}
		if (test.bit8) {
			test.bit8 = 0;
		} else {
			test.bit8 = 1;
		}*/
		if (test.flags & SB_BIT_1) {
			test.flags &= ~SB_BIT_1;
		} else {
			test.flags |= SB_BIT_1;
		}
		if (test.flags & SB_BIT_2) {
			test.flags &= ~SB_BIT_2;
		} else {
			test.flags |= SB_BIT_2;
		}
		if (test.flags & SB_BIT_3) {
			test.flags &= ~SB_BIT_3;
		} else {
			test.flags |= SB_BIT_3;
		}
		if (test.flags & SB_BIT_4) {
			test.flags &= ~SB_BIT_4;
		} else {
			test.flags |= SB_BIT_4;
		}
		if (test.flags & SB_BIT_5) {
			test.flags &= ~SB_BIT_5;
		} else {
			test.flags |= SB_BIT_5;
		}
		if (test.flags & SB_BIT_6) {
			test.flags &= ~SB_BIT_6;
		} else {
			test.flags |= SB_BIT_6;
		}
		if (test.flags & SB_BIT_7) {
			test.flags &= ~SB_BIT_7;
		} else {
			test.flags |= SB_BIT_7;
		}
		if (test.flags & SB_BIT_8) {
			test.flags &= ~SB_BIT_8;
		} else {
			test.flags |= SB_BIT_8;
		}
	}

	ns_stop = sb_time_nsec();

	printf("start: %llu\nstop : %llu\nspan : %llu\n", ns_start, ns_stop, (ns_stop - ns_start));

	fgetc(stdin);

	return 0;
}