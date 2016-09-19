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

#ifndef __SB_CORE_ERROR_H
#define __SB_CORE_ERROR_H


#include "stdincl.h"


typedef uint32_t sb_error_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_error_t _sb_error_get();
	SBAPI sb_error_t _sb_error_get_param();
	/*SBAPI*/ void _sb_error_set(sb_error_t _errno);
	/*SBAPI*/ void _sb_error_set_param(sb_error_t _errparam);
	/*SBAPI*/ void _sb_error_set_ex(sb_error_t _errno, sb_error_t _errparam);
	/*SBAPI*/ void _sb_error_reset();
	/*SBAPI*/ void _sb_error_fatal_ex(const char *file, const char *func, const uint32_t line, sb_error_t _errno, sb_error_t _errparam);
	/*SBAPI*/ void _sb_error_fatal(const char *file, const char *func, const uint32_t line, sb_error_t _errno);
	SBAPI void sb_error_print();

#ifdef __cplusplus
}
#endif


#ifdef SB_ERROR_REPORTING
#	define sb_error_get()					_sb_error_get()
#	define sb_error_get_param()				_sb_error_get_param()
#	define sb_error_set(x)					_sb_error_set(x)
#	define sb_error_set_param(x)			_sb_error_set_param(x)
#	define sb_error_set_ex(x, y)			_sb_error_set_ex(x, y)
#	define sb_error_reset()					_sb_error_reset()
#else
#	define sb_error_get()					SB_ERROR_SUCCESS
#	define sb_error_get_param()				SB_ERROR_SUCCESS
#	define sb_error_set(x)
#	define sb_error_set_param(x)
#	define sb_error_set_ex(x, y)
#	define sb_error_reset()
#endif

#define sb_error_fatal_ex(x, y)				_sb_error_fatal_ex(__FILE_LOCAL__, __func__, __LINE__, x, y)
#define sb_error_fatal(x)					_sb_error_fatal(__FILE_LOCAL__, __func__, __LINE__, x)

#define SB_ERROR_SUCCESS					0
#define SB_ERROR_NULL_PTR					1
#define SB_ERROR_PARAM_INVALID				2
#define SB_ERROR_PARAM_RANGE				3
#define SB_ERROR_FAILSAFE					4
#define SB_ERROR_FATAL_UNKNOWN				5
#define SB_ERROR_FATAL_OUT_OF_MEMORY		6
#define SB_ERROR_FATAL_PTR_INVALID			7
#define SB_ERROR_INITIALIZATION				8
#define SB_ERROR_FATAL_LOCK_FAILURE			9
#define SB_ERROR_DESCRIPTOR_INVALID			10
#define SB_ERROR_VALUE_INVALID				11
#define SB_ERROR_ENTRY_NOT_FOUND			12
#define SB_ERROR_FUNCTIONALITY				13
#define SB_ERROR_CLEANUP					14
#define SB_ERROR_NOERR_SIMULATION			0xBEEFCAFE
#define SB_ERROR_NOERR_SIMULATION_PARAM		0xDEAFBEE5


#endif
