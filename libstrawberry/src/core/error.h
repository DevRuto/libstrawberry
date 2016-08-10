#ifndef __SB_CORE_ERROR_H
#define __SB_CORE_ERROR_H

#include <stdint.h>

#include "../core/sbapi.h"


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
	/*SBAPI*/ void _sb_error_fatal_ex(const char *file, const char *func, const int line, sb_error_t _errno, sb_error_t _errparam);
	/*SBAPI*/ void _sb_error_fatal(const char *file, const char *func, const int line, sb_error_t _errno);

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
#	define sb_error_get()
#	define sb_error_get_param()
#	define sb_error_set(x)
#	define sb_error_set_param(x)
#	define sb_error_set_ex(x, y)
#	define sb_error_reset()
#endif

#define sb_error_fatal_ex(x, y)				_sb_error_fatal_ex(SB_DIAG_FILE, SB_DIAG_FUNC, SB_DIAG_LINE, x, y)
#define sb_error_fatal(x)					_sb_error_fatal(SB_DIAG_FILE, SB_DIAG_FUNC, SB_DIAG_LINE, x)

#define SB_ERROR_SUCCESS					0
#define SB_ERROR_NULL_PTR					1
#define SB_ERROR_PARAM_INVALID				2
#define SB_ERROR_PARAM_RANGE				3
#define SB_ERROR_FAILSAFE					4
#define SB_ERROR_FATAL_UNKNOWN				5
#define SB_ERROR_FATAL_OUT_OF_MEMORY		6
#define SB_ERROR_FATAL_PTR_INVALID			7
#define SB_ERROR_INITIALIZATION				8


#endif
