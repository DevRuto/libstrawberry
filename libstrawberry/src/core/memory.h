/*****************************************************************************
**                                                                          **
**  This file is part of libstrawberry.                                     **
**                                                                          **
**  libstrawberry is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by    **
**  the Free Software Foundation, either version 3 of the License, or       **
**  (at your option) any later version.                                     **
**                                                                          **
**  libstrawberry is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **
**  GNU General Public License for more details.                            **
**                                                                          **
**  You should have received a copy of the GNU General Public License       **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                          **
******************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CORE_MEMORY_H
#define __SB_CORE_MEMORY_H


#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sbapi.h"
#include "types/bool.h"


#define SB_PRIORITY_MEMORY					100


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_memory_set_malloc(void*(*func)(sb_size_t size));
	SBAPI void sb_memory_set_free(void(*func)(void *ptr));
	SBAPI void sb_memory_set_realloc(void*(*func)(void *ptr, sb_size_t size));
	SBAPI void sb_memory_set_memcpy(void*(*func)(void *dst, void *src, sb_size_t size));
	SBAPI void sb_memory_set_memset(void*(*func)(void *dst, int value, sb_size_t size));
	SBAPI void sb_memory_set_memcmp(int(*func)(void *cmp1, void *cmp2, sb_size_t size));

	SBAPI void* sb_malloc(sb_size_t size);
	SBAPI void* sb_calloc(sb_size_t size);
	SBAPI void* sb_realloc(void *ptr, sb_size_t size);
	SBAPI void* sb_cpyalloc(void *ptr, sb_size_t size);
	SBAPI void* sb_ntcpyalloc(void *ptr, sb_size_t size);
	SBAPI void sb_free(void *ptr);
	SBAPI void sb_memcpy(void *dst, void *src, sb_size_t size);
	SBAPI void sb_memset(void *dst, int value, sb_size_t size);
	SBAPI int sb_memcmp(void *cmp1, void *cmp2, sb_size_t size);
	SBAPI sb_bool_t sb_memequ(void *cmp1, void *cmp2, sb_size_t size);
	SBAPI void sb_strcpy(void *dst, const char *str);
	SBAPI void sb_strappend(void **dst, const char *str);

	SBAPI void sb_memdump_ex(void *src, sb_size_t size, sb_size_t columns);
	SBAPI void sb_memdump(void *src, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
