#ifndef __SB_CORE_MEMORY_H
#define __SB_CORE_MEMORY_H


#include <stdint.h>

#include "sbapi.h"
#include "types/bool.h"


#define SB_PRIORITY_MEMORY					100


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_memory_set_malloc(void*(*func)(size_t size));
	SBAPI void sb_memory_set_free(void(*func)(void *ptr));
	SBAPI void sb_memory_set_realloc(void*(*func)(void *ptr, size_t size));
	SBAPI void sb_memory_set_memcpy(void*(*func)(void *dst, void *src, size_t size));
	SBAPI void sb_memory_set_memset(void*(*func)(void *dst, int value, size_t size));
	SBAPI void sb_memory_set_memcmp(int(*func)(void *cmp1, void *cmp2, size_t size));

	SBAPI void* sb_malloc(size_t size);
	SBAPI void sb_free(void *ptr);
	SBAPI void* sb_realloc(void *ptr, size_t size);
	SBAPI void sb_memcpy(void *dst, void *src, size_t size);
	SBAPI void sb_memset(void *dst, int value, size_t size);
	SBAPI int sb_memcmp(void *cmp1, void *cmp2, size_t size);
	SBAPI sb_bool_t sb_memequ(void *cmp1, void *cmp2, size_t size);
	SBAPI void sb_strcpy(void *dst, const char *str);
	SBAPI void sb_strappend(void **dst, const char *str);

	SBAPI void sb_memdump_ex(void *src, size_t size, size_t columns);
	SBAPI void sb_memdump(void *src, size_t size);

#ifdef __cplusplus
}
#endif


#endif
