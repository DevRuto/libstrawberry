#include "../../stdincl.h"
#include <libstrawberry/crypto/symmetric/rabbit.h>

static uint8_t keys[][16] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x91, 0x28, 0x13, 0x29, 0x2E, 0x3D, 0x36, 0xFE, 0x3B, 0xFC, 0x62, 0xF1, 0xDC, 0x51, 0xC3, 0xAC },
	{ 0x83, 0x95, 0x74, 0x15, 0x87, 0xE0, 0xC7, 0x33, 0xE9, 0xE9, 0xAB, 0x01, 0xC0, 0x9B, 0x00, 0x43 }
};

static uint8_t results[][48] = {
	{ 0xB1, 0x57, 0x54, 0xF0, 0x36, 0xA5, 0xD6, 0xEC, 0xF5, 0x6B, 0x45, 0x26, 0x1C, 0x4A, 0xF7, 0x02, 0x88, 0xE8, 0xD8, 0x15, 0xC5, 0x9C, 0x0C, 0x39, 0x7B, 0x69, 0x6C, 0x47, 0x89, 0xC6, 0x8A, 0xA7, 0xF4, 0x16, 0xA1, 0xC3, 0x70, 0x0C, 0xD4, 0x51, 0xDA, 0x68, 0xD1, 0x88, 0x16, 0x73, 0xD6, 0x96 },
	{ 0x3D, 0x2D, 0xF3, 0xC8, 0x3E, 0xF6, 0x27, 0xA1, 0xE9, 0x7F, 0xC3, 0x84, 0x87, 0xE2, 0x51, 0x9C, 0xF5, 0x76, 0xCD, 0x61, 0xF4, 0x40, 0x5B, 0x88, 0x96, 0xBF, 0x53, 0xAA, 0x85, 0x54, 0xFC, 0x19, 0xE5, 0x54, 0x74, 0x73, 0xFB, 0xDB, 0x43, 0x50, 0x8A, 0xE5, 0x3B, 0x20, 0x20, 0x4D, 0x4C, 0x5E },
	{ 0x0C, 0xB1, 0x0D, 0xCD, 0xA0, 0x41, 0xCD, 0xAC, 0x32, 0xEB, 0x5C, 0xFD, 0x02, 0xD0, 0x60, 0x9B, 0x95, 0xFC, 0x9F, 0xCA, 0x0F, 0x17, 0x01, 0x5A, 0x7B, 0x70, 0x92, 0x11, 0x4C, 0xFF, 0x3E, 0xAD, 0x96, 0x49, 0xE5, 0xDE, 0x8B, 0xFC, 0x7F, 0x3F, 0x92, 0x41, 0x47, 0xAD, 0x3A, 0x94, 0x74, 0x28 }
};

sb_bool_t test_rabbit() {
	sb_bool_t valid = sb_true;

	sb_crypto_rabbit_ctx_t ctx;

	uint32_t i, ct[12], pt[12], tb[12];
	sb_memset(ct, 0xF8, sizeof(ct));
	sb_memset(pt, 0, sizeof(pt));

	//status("rabbit", "hardcoded test vectors", status_info);
	for (i = 0; i < 3; ++i) {
		sb_crypto_rabbit_init(&ctx, keys[i], 0);

		sb_crypto_rabbit_encrypt(&ctx, ct, pt, sizeof(pt));
		if (!sb_memequ(ct, results[i], sizeof(ct))) {
			valid = sb_false;
			status("rabbit e", "https://tools.ietf.org/html/rfc4503#appendix-A.1", status_failed);
		} else {
			status("rabbit e", "https://tools.ietf.org/html/rfc4503#appendix-A.1", status_passed);
		}

		sb_crypto_rabbit_reset(&ctx);
		sb_crypto_rabbit_decrypt(&ctx, tb, ct, sizeof(ct));
		if (!sb_memequ(pt, tb, sizeof(pt))) {
			valid = sb_false;
			status("rabbit d", "https://tools.ietf.org/html/rfc4503#appendix-A.1", status_failed);
		} else {
			status("rabbit d", "https://tools.ietf.org/html/rfc4503#appendix-A.1", status_passed);
		}
	}

	//status("rabbit", "soft [255 / (i + 1)]", status_info);
	for (i = 0; i < 10; ++i) {
		sb_memset(pt, 255 / (i + 1), sizeof(pt));

		sb_crypto_rabbit_init(&ctx, keys[1], 0);
		sb_crypto_rabbit_encrypt(&ctx, ct, pt, sizeof(pt));
		sb_crypto_rabbit_reset(&ctx);
		sb_crypto_rabbit_decrypt(&ctx, tb, ct, sizeof(ct));

		if (!sb_memequ(pt, tb, sizeof(pt))) {
			valid = sb_false;
			status("rabbit", "255 / (i + 1)", status_failed);
		} else {
			status("rabbit", "255 / (i + 1)", status_passed);
		}
	}

	return valid;
}
