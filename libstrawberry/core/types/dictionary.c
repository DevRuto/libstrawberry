/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

#define __FILE_LOCAL__						"core/types/dictionary.c"

#include "./dictionary.h"

#include "../memory.h"
#include "../error.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-07-30");


sb_bool_t sb_dictionary_init(sb_dictionary_t *dictionary, sb_size_t size) {
	sb_error_reset();

	if (!dictionary) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	sb_memset(dictionary, 0, sizeof(*dictionary));

	dictionary->__size = size;
	dictionary->entries = sb_calloc_u((sizeof(*dictionary->entries) * dictionary->__size));

	return sb_true;
}


sb_bool_t sb_dictionary_clear(sb_dictionary_t *dictionary) {
	sb_error_reset();

	if (!dictionary) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (dictionary->entries) {
		sb_size_t i;
		sb_dictionary_entry_t *entry;
		//for (i = 0; i < dictionary->__size; ++i) {
		for (i = dictionary->__size; i--;) {
			entry = &dictionary->entries[i];
			if (entry->key) {
				entry->key = sb_free(entry->key);
			}
		}
		dictionary->entries = sb_free(dictionary->entries);
	}

	sb_memset(dictionary, 0, sizeof(*dictionary));

	return sb_true;
}


sb_bool_t sb_dictionary_get_index(sb_dictionary_t *dictionary, const char *key, sb_size_t *index) {
	sb_error_reset();

	if (!dictionary) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!dictionary->entries) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	if (key) {
		sb_size_t i, keylen = strlen(key);
		sb_dictionary_entry_t *entry;
		//for (i = 0; i < dictionary->__size; ++i) {
		for (i = dictionary->__size; i--;) {
			entry = &dictionary->entries[i];
			if (entry->key && (entry->key_size == keylen) && sb_memequ((void*)key, entry->key, keylen)) {
				if (index) {
					*index = i;
				}
				return sb_true;
			}
		}
	} else {
		sb_size_t i;
		//for (i = 0; i < dictionary->__size; ++i) {
		for (i = dictionary->__size; i--;) {
			if (!dictionary->entries[i].key) {
				if (index) {
					*index = i;
				}
				return sb_true;
			}
		}
	}

	return sb_false;
}


sb_dictionary_entry_t* sb_dictionary_get(sb_dictionary_t *dictionary, const char *key) {
	sb_error_reset();

	if (!dictionary) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return NULL;
	}

	if (!key) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return NULL;
	}

	if (!dictionary->entries) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 3);
		return NULL;
	}

	sb_size_t i, key_size = strlen(key);
	sb_dictionary_entry_t *entry;
	//for (i = 0; i < dictionary->__size; ++i) {
	for (i = dictionary->__size; i--;) {
		entry = &dictionary->entries[i];
		if (entry->key && (entry->key_size == key_size) && sb_memequ((void*)key, entry->key, key_size)) {
			return entry;
		}
	}

	sb_error_set(SB_ERROR_ENTRY_NOT_FOUND);
	return NULL;
}


sb_bool_t sb_dictionary_set(sb_dictionary_t *dictionary, const char *key, void *value) {
	sb_error_reset();

	if (!dictionary) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!key) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 3);
		return sb_false;
	}

	if (!dictionary->entries) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	sb_size_t index = 0;
	if (!sb_dictionary_get_index(dictionary, key, &index)) {
		if (dictionary->count == dictionary->__size) {
			index = (dictionary->__size)++;
			dictionary->entries = sb_realloc_u(dictionary->entries, sizeof(*dictionary->entries) * dictionary->__size);

			sb_dictionary_entry_t *entry = &dictionary->entries[index];
			entry->key_size = strlen(key);
			entry->key = sb_ntcpyalloc_u((void*)key, entry->key_size);
			entry->value = value;
			++(dictionary->count);
		} else {
			if (!sb_dictionary_get_index(dictionary, NULL, &index)) {
				sb_error_set(SB_ERROR_VALUE_INVALID);
				return sb_false;
			} else {
				sb_dictionary_entry_t *entry = &dictionary->entries[index];
				entry->key_size = strlen(key);
				entry->key = sb_ntcpyalloc_u((void*)key, entry->key_size);
				entry->value = value;
				++(dictionary->count);
			}
		}
	} else {
		dictionary->entries[index].value = value;
	}

	return sb_true;
}
