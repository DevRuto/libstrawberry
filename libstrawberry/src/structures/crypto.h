#ifndef SB_STRUCT_CRYPTO_H
#define SB_STRUCT_CRYPTO_H


#include <stdint.h>

#include "../core/sbapi.h"
#include "../core/types/bool.h"


typedef struct sb_crypto {
	uint16_t *types;
	void **ptrs;
	uint16_t size;
} sb_crypto_t;


#define SB_CRYPTO_FLAG_ASYMMETRIC			32768

#define SB_CRYPTO_RIJNDAEL					(                            1)
#define SB_CRYPTO_DIFFIEHELLMAN				(SB_CRYPTO_FLAG_ASYMMETRIC & 1)


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_init(sb_crypto_t *crypto);
	SBAPI void sb_crypto_clear(sb_crypto_t *crypto);
	SBAPI sb_bool_t sb_crypto_entry_add(sb_crypto_t *crypto, uint16_t type, void *data, uint16_t *index);
	/*SBAPI sb_bool_t sb_crypto_entry_remove(sb_crypto_t *crypto, uint16_t index); // not sure if this is worth implementing
	SBAPI sb_bool_t sb_crypto_entry_find(sb_crypto_t *crypto, uint16_t type, void *data, uint16_t *index);*/
	SBAPI size_t sb_crypto_block_calculate(sb_crypto_t *crypto, size_t have_size);
	SBAPI sb_bool_t sb_crypto_block_encrypt(sb_crypto_t *crypto, uint8_t *out, uint8_t *in, size_t size);
	SBAPI sb_bool_t sb_crypto_block_decrypt(sb_crypto_t *crypto, uint8_t *out, uint8_t *in, size_t size);

#ifdef __cplusplus
}
#endif


#endif
