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
**    // TODO Memory alignment?
**
*/

#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	define mlock						VirtualLock
#	define munlock						VirtualUnlock
#else
#	include <sys/mman.h>
#endif

#include "error.h"


IDENTID("memory.c", "0.1", "2", "2016-08-14");


void* sb_malloc_u(sb_size_t size) {
	void *ptr = malloc(size);
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_OUT_OF_MEMORY);
	}
	return ptr;
}


void* sb_malloc_s(sb_size_t size) {
	void *ptr = sb_malloc_u(size);

	int err;
	if ((err = mlock(ptr, size))) {
		sb_free(ptr);
		sb_error_fatal_ex(SB_ERROR_FATAL_LOCK_FAILURE, err);
	} else {
		return ptr;
	}

	return NULL;
}


void* sb_calloc_u(sb_size_t size) {
	void *ptr = sb_malloc_u(size);
	sb_memset(ptr, 0, size);
	return ptr;
}


void* sb_calloc_s(sb_size_t size) {
	void *ptr = sb_malloc_s(size);
	sb_memset(ptr, 0, size);
	return ptr;
}


void* sb_realloc_u(void *ptr, sb_size_t size) {
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	void *nptr = realloc(ptr, size);
	if (!nptr) {
		sb_error_fatal(SB_ERROR_FATAL_OUT_OF_MEMORY);
	}
	return nptr;
}


void* sb_realloc_s(void *ptr, sb_size_t size) {
	void *p = sb_realloc_u(ptr, size);

	int err;
	if ((err = mlock(p, size))) {
		sb_free(p);
		sb_error_fatal_ex(SB_ERROR_FATAL_LOCK_FAILURE, err);
	} else {
		return p;
	}

	return NULL;
}


void* sb_cpyalloc_u(void *ptr, sb_size_t size) {
	if (ptr) {
		if (size) {
			void *p = sb_malloc_u(size);
			sb_memcpy(p, ptr, size);
			return p;
		}
	} else {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	return NULL;
}


void* sb_cpyalloc_s(void *ptr, sb_size_t size) {
	if (ptr) {
		if (size) {
			void *p = sb_malloc_s(size);
			sb_memcpy(p, ptr, size);
			return p;
		}
	} else {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	return NULL;
}


void* sb_ntcpyalloc_u(void *ptr, sb_size_t size) {
	if (ptr) {
		if (size) {
			void *p = sb_cpyalloc_u(ptr, size + 1);
			((uint8_t*)p)[size] = 0;
			return p;
		}
	} else {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	return NULL;
}


void* sb_ntcpyalloc_s(void *ptr, sb_size_t size) {
	if (ptr) {
		if (size) {
			void *p = sb_cpyalloc_s(ptr, size + 1);
			((uint8_t*)p)[size] = 0;
			return p;
		}
	} else {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	return NULL;
}


void sb_free(void *ptr) {
	if (!ptr) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	free(ptr);
}


void sb_memcpy(void *dst, void *src, sb_size_t size) {
	if (!dst || !src) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	if (dst == src) {
		return;
	}
	memcpy(dst, src, size);
}


void sb_memset(void *dst, int value, sb_size_t size) {
	if (!dst) {
		sb_error_fatal(SB_ERROR_FATAL_PTR_INVALID);
	}
	memset(dst, value, size);
}


int sb_memcmp(void *cmp1, void *cmp2, sb_size_t size) {
	int cmp = 2147483647;
	if (cmp1 && cmp2) {
		cmp = memcmp(cmp1, cmp2, size);
	}
	return cmp;
}


sb_bool_t sb_memequ(void *cmp1, void *cmp2, sb_size_t size) {
	return (sb_memcmp(cmp1, cmp2, size) == 0);
}


void sb_strcpy(void *dst, const char *str) {
	if (dst && str) {
		sb_memcpy(dst, (void*)str, strlen(str));
	}
}


void sb_strappend(void **dst, const char *str) {
	if (dst && *dst && str) {
		sb_size_t size = strlen(str);
		sb_memcpy(*dst, (void*)str, size);
		*dst = (void*)(((uintptr_t)*dst) + size);
	}
}


void sb_memdump_ex(void *src, sb_size_t size, sb_size_t columns) {
	if (!src) {
		puts("memdump: invalid pointer");
		return;
	}
	if (src && size && columns) {
		uint8_t *ptr = src;
		sb_size_t i = 0, c = 0;
		for (i = 0; i < size; ++i) {
			printf("%02X ", *(ptr++));
			if (++c == columns) {
				c = 0;
				puts("");
			}
		}
	}
}


void sb_memdump(void *src, sb_size_t size) {
	sb_memdump_ex(src, size, 16);
}
