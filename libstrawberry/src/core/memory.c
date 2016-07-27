#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"


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
	return (__sb_malloc ? __sb_malloc : malloc)(size);
}

void sb_free(void *ptr) {
	(__sb_free ? __sb_free : free)(ptr);
}

void* sb_realloc(void *ptr, size_t size) {
	return (__sb_realloc ? __sb_realloc : realloc)(ptr, size);
}

void sb_memcpy(void *dst, void *src, size_t size) {
	(__sb_memcpy ? __sb_memcpy : memcpy)(dst, src, size);
}

void sb_memset(void *dst, int value, size_t size) {
	(__sb_memset ? __sb_memset : memset)(dst, value, size);
}

int sb_memcmp(void *cmp1, void *cmp2, size_t size) {
	return (__sb_memcmp ? __sb_memcmp : memcmp)(cmp1, cmp2, size);
}

sb_bool_t sb_memequ(void *cmp1, void *cmp2, size_t size) {
	return (sb_memcmp(cmp1, cmp2, size) == 0);
}

void sb_memdump_ex(void *src, size_t size, size_t columns) {
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