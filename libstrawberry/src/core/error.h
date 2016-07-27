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
	void _sb_error_set(sb_error_t _errno);
	void _sb_error_set_param(sb_error_t _errparam);
	void _sb_error_set_ex(sb_error_t _errno, sb_error_t _errparam);
	void _sb_error_reset();

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


#define SB_ERROR_SUCCESS					0
#define SB_ERROR_NULL_PTR					1
#define SB_ERROR_PARAM_INVALID				2
#define SB_ERROR_PARAM_RANGE				3
#define SB_ERROR_FAILSAFE					4


#endif
