#ifndef __SB_CRYPTO_SYMMETRIC_RIJNDAEL_H
#define __SB_CRYPTO_SYMMETRIC_RIJNDAEL_H


#include <stdint.h>

#include "../../core/sbapi.h"

#include "../blockmode.h"


typedef struct sb_crypto_rijndael_ctx {
	uint32_t *key_encrypt; // rijndael
	uint32_t *key_decrypt; // rijndael
	void *iv;
	uint8_t size; // rijndael
	uint8_t rounds; // rijndael
	uint16_t flags; // rijndael
	uint16_t modes;
	uint16_t mode_flags;
} sb_crypto_rijndael_ctx_t;


#define SB_CRYPTO_RIJNDAEL_BLOCK_SIZE		16

#define SB_CRYPTO_RIJNDAEL_128				1
#define SB_CRYPTO_RIJNDAEL_192				2
#define SB_CRYPTO_RIJNDAEL_256				3


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_rijndael_init(sb_crypto_rijndael_ctx_t *rijndael, uint8_t bits, void *key, uint16_t modes, uint16_t mode_flags, void *iv);
	SBAPI void sb_crypto_rijndael_clear(sb_crypto_rijndael_ctx_t *rijndael);
	SBAPI void sb_crypto_rijndael_encrypt(sb_crypto_rijndael_ctx_t *rijndael, void *out, void *in);
	SBAPI void sb_crypto_rijndael_decrypt(sb_crypto_rijndael_ctx_t *rijndael, void *out, void *in);

#ifdef __cplusplus
}
#endif


#endif
