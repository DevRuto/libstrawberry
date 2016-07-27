#ifndef SB_CRYPTO_SYMMETRIC_RIJNDAEL_H
#define SB_CRYPTO_SYMMETRIC_RIJNDAEL_H


#include <stdint.h>

#include "../../core/sbapi.h"

#include "../blockmode.h"


typedef struct sb_crypto_rijndael {
	uint32_t *key_encrypt;
	uint32_t *key_decrypt;
	sb_crypto_blockmode_t blockmode;
	uint8_t size;
	uint8_t rounds;
	uint16_t flags;
} sb_crypto_rijndael_t;


#define SB_CRYPTO_RIJNDAEL_SWAP(x)			(SB_ROTL32(x, 8) & 0x00FF00FF | SB_ROTR32(x, 8) & 0xFF00FF00)
#define SB_CRYPTO_RIJNDAEL_GET32(x)			(((uint32_t)(x)[0] << 24) ^ ((uint32_t)(x)[1] << 16) ^ ((uint32_t)(x)[2] << 8) ^ ((uint32_t)(x)[3]))
#define SB_CRYPTO_RIJNDAEL_PUT32(x, y)		{ (x)[0] = (uint8_t)((y) >> 24); (x)[1] = (uint8_t)((y) >> 16); (x)[2] = (uint8_t)((y) >> 8); (x)[3] = (uint8_t)(y); }


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_rijndael_init(sb_crypto_rijndael_t *rijndael, uint8_t bits, void *key);
	SBAPI void sb_crypto_rijndael_clear(sb_crypto_rijndael_t *rijndael);
	SBAPI void sb_crypto_rijndael_encrypt_block(sb_crypto_rijndael_t *rijndael, uint8_t out[16], uint8_t in[16]);
	SBAPI void sb_crypto_rijndael_decrypt_block(sb_crypto_rijndael_t *rijndael, uint8_t out[16], uint8_t in[16]);

#ifdef __cplusplus
}
#endif


#endif
