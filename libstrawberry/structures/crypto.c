#include "crypto.h"
#include "../core/memory.h"

sb_crypto_t* sb_crypto_alloc() {
	sb_crypto_t *crypto = (sb_crypto_t*)sb_malloc(sizeof(sb_crypto_t));
	if (crypto) {
		crypto->size = 0;
	}
}

void sb_crypto_free(sb_crypto_t* crypto) {
	if (crypto) {
		sb_free(crypto);
	}
}

sb_bool_t sb_crypto_entry_add(sb_crypto_t **crypto, uint16_t type, void *data, uint16_t *index) {
	if (!crypto || !*crypto || !type || !data) {
		return sb_false;
	}

	uint16_t idx = (*crypto)->size++;

	sb_crypto_t *ncrypto = (sb_crypto_t*)sb_realloc(crypto, sizeof(**crypto) + (sizeof(sb_crypto_entry_t) * (*crypto)->size));
	if (ncrypto) {
		*crypto = ncrypto;
		(*crypto)->entries[idx].type = type;
		(*crypto)->entries[idx].data = data;

		if (index) {
			*index = idx;
		}

		return sb_true;
	}

	return sb_false;
}

/*sb_bool_t sb_crypto_entry_remove(sb_crypto_t *crypto, uint16_t index) {
	return sb_false;
}

sb_bool_t sb_crypto_entry_find(sb_crypto_t *crypto, uint16_t type, void *data, uint16_t *index) {
	return sb_false;
}*/
