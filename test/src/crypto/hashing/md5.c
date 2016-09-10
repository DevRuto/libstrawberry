#include "../../stdincl.h"
#include <string.h>
#include "../../../../libstrawberry/crypto/hashing/md5.h"


static uint8_t vectors_input[3][48] = {
	"",
	"The quick brown fox jumps over the lazy dog",
	"The quick brown fox jumps over the lazy dog."
};
static uint8_t vectors[3][16] = {
	{ 0xD4, 0x1D, 0x8C, 0xD9, 0x8F, 0x00, 0xB2, 0x04, 0xE9, 0x80, 0x09, 0x98, 0xEC, 0xF8, 0x42, 0x7E },
	{ 0x9E, 0x10, 0x7D, 0x9D, 0x37, 0x2B, 0xB6, 0x82, 0x6B, 0xD8, 0x1D, 0x35, 0x42, 0xA4, 0x19, 0xD6 },
	{ 0xE4, 0xD9, 0x09, 0xC2, 0x90, 0xD0, 0xFB, 0x1C, 0xA0, 0x68, 0xFF, 0xAD, 0xDF, 0x22, 0xCB, 0xD0 }
};

sb_bool_t test_md5() {
	sb_bool_t valid = sb_true;

	uint8_t buffer[16];

	uint32_t i;
	for (i = 0; i < 3; ++i) {
		sb_crypto_md5(buffer, vectors_input[i], strlen((char*)vectors_input[i]));
		if (!sb_memequ(buffer, vectors[i], 16)) {
			valid = sb_false;
			status("md5", "https://en.wikipedia.org/wiki/MD5", status_failed);
		} else {
			status("md5", "https://en.wikipedia.org/wiki/MD5", status_passed);
		}
	}

	return valid;
}
