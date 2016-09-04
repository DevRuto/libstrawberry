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

#include "dictionary.h"

#include "../memory.h"


IDENTID("dictionary.c", "0.1", "1", "2016-07-30");


void sb_dictionary_init(sb_dictionary_t *dictionary, sb_size_t size) {
	if (!dictionary) {
		return;
	}

	sb_memset(dictionary, 0, sizeof(*dictionary));

	dictionary->__size = size;

	sb_size_t msize = (sizeof(*dictionary->entries) * dictionary->__size);
	dictionary->entries = sb_calloc_u(msize);
}


void sb_dictionary_clear(sb_dictionary_t *dictionary) {
	if (!dictionary) {
		return;
	}

	if (dictionary->entries) {
		sb_size_t i;
		sb_dictionary_entry_t *entry;
		for (i = 0; i < dictionary->__size; ++i) {
			entry = &dictionary->entries[i];
			if (entry->key) {
				sb_free(entry->key);
				entry->key = NULL;
			}
		}
		sb_free(dictionary->entries);
	}

	sb_memset(dictionary, 0, sizeof(*dictionary));
}


sb_bool_t sb_dictionary_get_index(sb_dictionary_t *dictionary, const char *key, sb_size_t *index) {
	if (!dictionary || !dictionary->entries) {
		return sb_false;
	}

	if (key) {
		sb_size_t i, keylen = strlen(key);
		sb_dictionary_entry_t *entry;
		for (i = 0; i < dictionary->__size; ++i) {
			entry = &dictionary->entries[i];
			if (entry->key && strlen(entry->key) == keylen && sb_memequ((void*)key, entry->key, keylen)) {
				if (index) {
					*index = i;
				}
				return sb_true;
			}
		}
	} else {
		sb_size_t i;
		for (i = 0; i < dictionary->__size; ++i) {
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
	if (!dictionary || !dictionary->entries || !key) {
		return NULL;
	}

	sb_size_t i, keylen = strlen(key);
	sb_dictionary_entry_t *entry;
	for (i = 0; i < dictionary->__size; ++i) {
		entry = &dictionary->entries[i];
		if (entry->key && strlen(key) == keylen && sb_memequ((void*)key, entry->key, keylen)) {
			return entry;
		}
	}

	return NULL;
}


sb_bool_t sb_dictionary_set(sb_dictionary_t *dictionary, const char *key, void *value) {
	if (!dictionary || !dictionary->entries || !key) {
		return sb_false;
	}

	sb_size_t index;
	if (dictionary->count == dictionary->__size) {
		index = dictionary->__size++;
		dictionary->entries = sb_realloc_u(dictionary->entries, sizeof(*dictionary->entries) * dictionary->__size);
	} else {
		if (!sb_dictionary_get_index(dictionary, NULL, &index)) {
			// error
			return sb_false;
		}
	}

	dictionary->entries[index].key = sb_ntcpyalloc_u((void*)key, strlen(key));
	dictionary->entries[index].value = value;

	++(dictionary->count);

	return sb_true;
}
