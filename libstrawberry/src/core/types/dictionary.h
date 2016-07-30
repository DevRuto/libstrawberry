#ifndef _SB_CORE_TYPE_DICTIONARY_H
#define _SB_CORE_TYPE_DICTIONARY_H


#include <stdint.h>
#include <stddef.h>

#include "bool.h"
#include "../sbapi.h"


typedef struct sb_dictionary_entry {
	char *key;
	void *value;
} sb_dictionary_entry_t;

typedef struct sb_dictionary {
	sb_dictionary_entry_t *entries;
	sb_size_t __size;
	sb_size_t count;
} sb_dictionary_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_dictionary_init(sb_dictionary_t *dictionary, sb_size_t size);
	SBAPI void sb_dictionary_clear(sb_dictionary_t *dictionary);
	SBAPI sb_bool_t sb_dictionary_get_index(sb_dictionary_t *dictionary, const char *key, sb_size_t *index);
	SBAPI sb_dictionary_entry_t* sb_dictionary_get(sb_dictionary_t *dictionary, const char *key);
	SBAPI sb_bool_t sb_dictionary_set(sb_dictionary_t *dictionary, const char *key, void *value);

#ifdef __cplusplus
}
#endif


#endif
