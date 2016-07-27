#ifndef SB_CRYPTO_BLOCKMODE_H
#define SB_CRYPTO_BLOCKMODE_H


#include <stdint.h>


typedef struct sb_crypto_blockmode {
	void *iv;
	uint16_t modes;
	uint16_t flags;
} sb_crypto_blockmode_t;


#define SB_CRYPTO_BLOCKMODE_CBC				32768

#define SB_CRYPTO_BLOCKFLAG_EXPLICIT_IV		32768


#endif
