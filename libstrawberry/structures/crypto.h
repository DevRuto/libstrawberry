#ifndef SB_STRUCT_CRYPTO_H
#define SB_STRUCT_CRYPTO_H


#include <stdint.h>

#include "../core/types/bool.h"


typedef struct sb_crypto_entry {
	void *data;
	uint16_t type;
} sb_crypto_entry_t;

typedef struct sb_crypto {
	uint16_t size;
	sb_crypto_entry_t entries[];
} sb_crypto_t;


#define SB_CRYPTO_FLAG_ASYMMETRIC			32768

#define SB_CRYPTO_RIJNDAEL					(                            1)
#define SB_CRYPTO_DIFFIEHELLMAN				(SB_CRYPTO_FLAG_ASYMMETRIC & 1)


#ifdef __cplusplus
extern "C" {
#endif

	sb_crypto_t* sb_crypto_alloc();
	void sb_crypto_free(sb_crypto_t *crypto);
	sb_bool_t sb_crypto_entry_add(sb_crypto_t **crypto, uint16_t type, void *data, uint16_t *index);
	/*sb_bool_t sb_crypto_entry_remove(sb_crypto_t *crypto, uint16_t index); // not sure if this is worth implementing
	sb_bool_t sb_crypto_entry_find(sb_crypto_t *crypto, uint16_t type, void *data, uint16_t *index);*/
	

#ifdef __cplusplus
}
#endif


#endif
