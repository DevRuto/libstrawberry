#include "identid.h"
IDENTID("memory.c", "0.1", "1", "2016-07-30");

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "error.h"


static void*(*__sb_malloc)(size_t) = NULL;
static void(*__sb_free)(void*) = NULL;
static void*(*__sb_realloc)(void*, size_t) = NULL;
static void*(*__sb_memcpy)(void*, void*, size_t) = NULL;
static void*(*__sb_memset)(void*, int, size_t) = NULL;
static int(*__sb_memcmp)(void *cmp1, void *cmp2, size_t size) = NULL;

void sb_memory_set_malloc(void*(*func)(size_t size)) {
	__sb_malloc = func;
}

void sb_memory_set_free(void(*func)(void *ptr)) {
	__sb_free = func;
}

void sb_memory_set_realloc(void*(*func)(void *ptr, size_t size)) {
	__sb_realloc = func;
}

void sb_memory_set_memcpy(void*(*func)(void *dst, void *src, size_t size)) {
	__sb_memcpy = func;
}

void sb_memory_set_memset(void*(*func)(void *dst, int value, size_t size)) {
	__sb_memset = func;
}

void sb_memory_set_memcmp(int(*func)(void *cmp1, void *cmp2, size_t size)) {
	__sb_memcmp = func;
}


void* sb_malloc(size_t size) {
	void *ptr = (__sb_malloc ? __sb_malloc : malloc)(size);
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_OUT_OF_MEMORY);
	}
	return ptr;
}

void* sb_calloc(size_t size) {
	void *ptr = sb_malloc(size);
	sb_memset(ptr, 0, size);
	return ptr;
}

void* sb_realloc(void *ptr, size_t size) {
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	void *nptr = (__sb_realloc ? __sb_realloc : realloc)(ptr, size);
	if (!nptr) {
		sb_error_fatal(SB_ERROR_FATAL_OUT_OF_MEMORY);
	}
	return nptr;
}

void* sb_cpyalloc(void *ptr, size_t size) {
	if (ptr && size) {
		void *p = sb_malloc(size);
		sb_memcpy(p, ptr, size);
		return p;
	}
	return NULL;
}

void* sb_ntcpyalloc(void *ptr, size_t size) {
	if (ptr && size) {
		void *p = sb_cpyalloc(ptr, size + 1);
		((uint8_t*)p)[size] = 0;
		return p;
	}
	return NULL;
}

void sb_free(void *ptr) {
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	(__sb_free ? __sb_free : free)(ptr);
}

void sb_memcpy(void *dst, void *src, size_t size) {
	if (!dst || !src) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	(__sb_memcpy ? __sb_memcpy : memcpy)(dst, src, size);
}

void sb_memset(void *dst, int value, size_t size) {
	if (!dst) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	(__sb_memset ? __sb_memset : memset)(dst, value, size);
}

int sb_memcmp(void *cmp1, void *cmp2, size_t size) {
	if (cmp1 && cmp2) {
		return (__sb_memcmp ? __sb_memcmp : memcmp)(cmp1, cmp2, size);
	} else {
		return 2147483647;
	}
}

sb_bool_t sb_memequ(void *cmp1, void *cmp2, size_t size) {
	return (sb_memcmp(cmp1, cmp2, size) == 0);
}

void sb_strcpy(void *dst, const char *str) {
	if (dst && str) {
		sb_memcpy(dst, (void*)str, strlen(str));
	}
}

void sb_strappend(void **dst, const char *str) {
	if (dst && *dst && str) {
		size_t size = strlen(str);
		sb_memcpy(*dst, (void*)str, size);
		(uint8_t*)*dst += size;
	}
}

void sb_memdump_ex(void *src, size_t size, size_t columns) {
	if (!src) {
		printf("%s: invalid pointer (%p)\n", __func__, src);
		return;
	}
	if (src && size && columns) {
		uint8_t *ptr = src;
		size_t i = 0, c = 0;
		for (i = 0; i < size; ++i) {
			printf("%02X ", *(ptr++));
			if (++c == columns) {
				c = 0;
				puts("");
			}
		}
	}
}

void sb_memdump(void *src, size_t size) {
	sb_memdump_ex(src, size, 16);
}
