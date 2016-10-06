#include "../stdincl.h"
#include <libstrawberry/crypto/cipher.h>
#include <libstrawberry/crypto/keygen.h>
#include <libstrawberry/crypto/random.h>


sb_bool_t test_cipher() {
	sb_bool_t valid = sb_false;

	uint32_t key32[8], i;
	for (i = 8; i--;) {
		key32[i] = sb_random32();
	}

	sb_crypto_cipher_ctx_t cipher;
	sb_crypto_cipher_init(&cipher, SB_CRYPTO_CIPHER_RIJNDAEL, SB_CRYPTO_CIPHER_PAD_ISO979712, 0, SB_CRYPTO_RIJNDAEL_256, key32);

	uint8_t plain[20], ct[32], dt[32];
	sb_memset(plain, 0xAF, 20);
	sb_memset(ct, 0, 32);
	sb_memset(dt, 0, 32);

	sb_size_t poff = 0;

	sb_crypto_cipher_encrypt(&cipher, ct, plain, 20);
	sb_crypto_cipher_decrypt(&cipher, dt, ct, 32, &poff);

	if (poff == sizeof(plain)) {
		if (sb_memequ(plain, dt, poff)) {
			valid = sb_true;
		}
	}

	return valid;
}
