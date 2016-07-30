#include "../core/rcsid.h"
RCSID("crypto.c", "0.1", "1", "2016-07-29");

#include "crypto.h"
#include "../core/memory.h"
#include "../core/error.h"


void sb_crypto_init(sb_crypto_ctx_t *crypto) {
	sb_error_reset();

	if (crypto) {
		crypto->size = 0;
		crypto->types = (uint16_t*)sb_malloc(0);
		crypto->ptrs = (void**)sb_malloc(0);
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}

void sb_crypto_clear(sb_crypto_ctx_t* crypto) {
	sb_error_reset();

	if (crypto) {
		sb_free(crypto->types);
		sb_free(crypto->ptrs);
	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}
}

sb_bool_t sb_crypto_entry_add(sb_crypto_ctx_t *crypto, uint16_t type, void *data, uint16_t *index) {
	sb_error_reset();

	if (!crypto || !type || !data) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	uint16_t idx = crypto->size++;

	uint16_t *tptr = (uint16_t*)sb_realloc(crypto->types, sizeof(*crypto->types) * crypto->size);
	if (tptr) {
		void **eptr = (void**)sb_realloc(crypto->ptrs, sizeof(*crypto->ptrs) * crypto->size);
		if (eptr) {
			crypto->types = tptr;
			crypto->ptrs = eptr;

			crypto->types[idx] = type;
			crypto->ptrs[idx] = data;

			if (index) {
				*index = idx;
			}

			return sb_true;
		} else {
			sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		}
	} else {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
	}

	return sb_false;
}

/*sb_bool_t sb_crypto_entry_remove(sb_crypto_ctx_t *crypto, uint16_t index) {
	return sb_false;
}

sb_bool_t sb_crypto_entry_find(sb_crypto_ctx_t *crypto, uint16_t type, void *data, uint16_t *index) {
	return sb_false;
}*/

size_t sb_crypto_block_calculate(sb_crypto_ctx_t *crypto, size_t have_size) {
	sb_error_reset();

	if (crypto && crypto->size && crypto->types && crypto->ptrs) {
		size_t cs = have_size;

	} else {
		sb_error_set(SB_ERROR_NULL_PTR);
	}

	return 0;
}

sb_bool_t sb_crypto_block_encrypt(sb_crypto_ctx_t *crypto, uint8_t *out, uint8_t *in, size_t size) {
	return sb_false;
}

sb_bool_t sb_crypto_block_decrypt(sb_crypto_ctx_t *crypto, uint8_t *out, uint8_t *in, size_t size) {
	return sb_false;
}
