#ifndef SB_CORE_MEMORY_H
#define SB_CORE_MEMORY_H


#include <stdint.h>


#define SB_PRIORITY_MEMORY					100


#ifdef __cplusplus
extern "C" {
#endif

	void sb_memory_set_malloc(void*(*func)(size_t size));
	void sb_memory_set_free(void(*func)(void *ptr));
	void sb_memory_set_realloc(void*(*func)(void *ptr, size_t size));
	void sb_memory_set_memcpy(void*(*func)(void *dst, void *src, size_t size));
	void sb_memory_set_memset(void*(*func)(void *dst, int value, size_t size));

	void* sb_malloc(size_t size);
	void sb_free(void *ptr);
	void* sb_realloc(void *ptr, size_t size);
	void sb_memcpy(void *dst, void *src, size_t size);
	void sb_memset(void *dst, int value, size_t size);

#ifdef __cplusplus
}
#endif


#endif
