#include <stdlib.h>
#include <string.h>
#include "memory.h"


static void*(*__sb_malloc)(size_t) = NULL;
static void(*__sb_free)(void*) = NULL;
static void*(*__sb_realloc)(void*, size_t) = NULL;
static void*(*__sb_memcpy)(void*, void*, size_t) = NULL;
static void*(*__sb_memset)(void*, int, size_t) = NULL;

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