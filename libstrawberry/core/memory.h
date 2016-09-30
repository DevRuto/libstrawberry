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

#ifndef __SB_CORE_MEMORY_H
#define __SB_CORE_MEMORY_H


#include "./stdincl.h"

#include "./cli.h"

#include <string.h>


#define SB_PRIORITY_MEMORY					100


#if (SB_COMPILER == SB_COMPILER_ID_MSC)
#	define SB_MEM_BUFFER_ALLOC(type, name, size) \
											type *name = _malloca(size)
#	define SB_MEM_BUFFER_FREE(name)			_freea(size)
#else
#	define SB_MEM_BUFFER_ALLOC(type, name, size) \
											type name[size]
#	define SB_MEM_BUFFER_FREE(name)
#endif


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void* sb_malloc_u(sb_size_t size);
	SBAPI void* sb_malloc_s(sb_size_t size);
	SBAPI void* sb_calloc_u(sb_size_t size);
	SBAPI void* sb_calloc_s(sb_size_t size);
	SBAPI void* sb_realloc_u(void *ptr, sb_size_t size);
	SBAPI void* sb_realloc_s(void *ptr, sb_size_t size);
	SBAPI void* sb_cpyalloc_u(void *ptr, sb_size_t size);
	SBAPI void* sb_cpyalloc_s(void *ptr, sb_size_t size);
	SBAPI void* sb_ntcpyalloc_u(void *ptr, sb_size_t size);
	SBAPI void* sb_ntcpyalloc_s(void *ptr, sb_size_t size);
	SBAPI void* sb_free(void *ptr);

	SBAPI void sb_memcpy(void *dst, void *src, sb_size_t size);
	SBAPI void sb_memset(void *dst, int value, sb_size_t size);
	SBAPI int sb_memcmp(void *cmp1, void *cmp2, sb_size_t size);
#define sb_memequ(cmp1, cmp2, size) (sb_memcmp((cmp1), (cmp2), (size)) == 0)

	SBAPI void sb_strcpy(char *dst, const char *str);
	SBAPI void sb_strappend(char **dst, const char *str);

	SBAPI void sb_memdump_ex(void *src, sb_size_t size, sb_size_t columns);
	SBAPI void sb_memdump(void *src, sb_size_t size);
	SBAPI void sb_vmemdump_ex(const char *msg, void *src, sb_size_t size, sb_size_t columns);
	SBAPI void sb_vmemdump(const char *msg, void *src, sb_size_t size);
	SBAPI void sb_cvmemdump_ex(const char *msg, uint8_t color, void *src, sb_size_t size, sb_size_t columns);
	SBAPI void sb_cvmemdump(const char *msg, uint8_t color, void *src, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
