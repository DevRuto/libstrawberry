#include "../../stdincl.h"
#include "../../../../libstrawberry/src/crypto/hashing/ripemd160.h"

static char *tests[6] = {
	"a",
	"abc",
	"message digest",
	"abcdefghijklmnopqrstuvwxyz",
	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
};

static uint8_t results[6][20] = { // http://homes.esat.kuleuven.be/~bosselae/ripemd160.html
	{ 0x0B, 0xDC, 0x9D, 0x2D, 0x25, 0x6B, 0x3E, 0xE9, 0xDA, 0xAE, 0x34, 0x7B, 0xE6, 0xF4, 0xDC, 0x83, 0x5A, 0x46, 0x7F, 0xFE },
	{ 0x8E, 0xB2, 0x08, 0xF7, 0xE0, 0x5D, 0x98, 0x7A, 0x9B, 0x04, 0x4A, 0x8E, 0x98, 0xC6, 0xB0, 0x87, 0xF1, 0x5A, 0x0B, 0xFC },
	{ 0x5D, 0x06, 0x89, 0xEF, 0x49, 0xD2, 0xFA, 0xE5, 0x72, 0xB8, 0x81, 0xB1, 0x23, 0xA8, 0x5F, 0xFA, 0x21, 0x59, 0x5F, 0x36 },
	{ 0xF7, 0x1C, 0x27, 0x10, 0x9C, 0x69, 0x2C, 0x1B, 0x56, 0xBB, 0xDC, 0xEB, 0x5B, 0x9D, 0x28, 0x65, 0xB3, 0x70, 0x8D, 0xBC },
	{ 0x12, 0xA0, 0x53, 0x38, 0x4A, 0x9C, 0x0C, 0x88, 0xE4, 0x05, 0xA0, 0x6C, 0x27, 0xDC, 0xF4, 0x9A, 0xDA, 0x62, 0xEB, 0x2B },
	{ 0xB0, 0xE2, 0x0B, 0x6E, 0x31, 0x16, 0x64, 0x02, 0x86, 0xED, 0x3A, 0x87, 0xA5, 0x71, 0x30, 0x79, 0xB2, 0x1F, 0x51, 0x89 }
};

sb_bool_t test_ripemd160() {
	uint8_t digest[20];

	sb_bool_t valid = sb_true;

	uint32_t i;
	for (i = 0; i < 6; ++i) {
		sb_crypto_ripemd160(digest, tests[i], strlen(tests[i]));
		if (sb_memcmp(digest, results[i], 20)) {
			valid = sb_false;
			status("h ripemd160", "http://homes.esat.kuleuven.be/~bosselae/ripemd160.html", status_failed);
		} else {
			status("h ripemd160", "http://homes.esat.kuleuven.be/~bosselae/ripemd160.html", status_passed);
		}
	}

	return valid;
}