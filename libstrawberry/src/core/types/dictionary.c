/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU Lesser General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU Lesser General Public License for more details.                          **
**                                                                               **
**  You should have received a copy of the GNU Lesser General Public License     **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#include "../identid.h"
IDENTID("dictionary.c", "0.1", "1", "2016-07-30");

#include "dictionary.h"

#include "../memory.h"


void sb_dictionary_init(sb_dictionary_t *dictionary, sb_size_t size) {
	if (!dictionary) {
		return;
	}

	sb_memset(dictionary, 0, sizeof(*dictionary));

	dictionary->__size = size;

	sb_size_t msize = (sizeof(*dictionary->entries) * dictionary->__size);
	dictionary->entries = sb_calloc(msize);
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
		dictionary->entries = sb_realloc(dictionary->entries, sizeof(*dictionary->entries) * dictionary->__size);
	} else {
		if (!sb_dictionary_get_index(dictionary, NULL, &index)) {
			// error
			return sb_false;
		}
	}

	dictionary->entries[index].key = sb_ntcpyalloc((void*)key, strlen(key));
	dictionary->entries[index].value = value;

	++(dictionary->count);

	return sb_true;
}
