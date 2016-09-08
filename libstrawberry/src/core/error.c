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

#include "error.h"

#include <stdio.h>
#include <signal.h>


IDENTID("error.c", "0.2", "1", "2016-09-08");


static sb_error_t __sb_errno = 0;
static sb_error_t __sb_errparam = 0;


sb_error_t _sb_error_get() {
	return __sb_errno;
}


sb_error_t _sb_error_get_param() {
	return __sb_errparam;
}


void _sb_error_set(sb_error_t _errno) {
	__sb_errno = _errno;
}


void _sb_error_set_param(sb_error_t _errparam) {
	__sb_errparam = _errparam;
}


void _sb_error_set_ex(sb_error_t _errno, sb_error_t _errparam) {
	__sb_errno = _errno;
	__sb_errparam = _errparam;
}


void _sb_error_reset() {
	__sb_errno = 0;
	__sb_errparam = 0;
}


void _sb_error_fatal_ex(const char *file, const char *func, const int line, sb_error_t _errno, sb_error_t _errparam) {
	printf(
		" === STRAWBERRY - FATAL ERROR ===\n"
		"  By: %s\n"
		"  In: %s:%d\n"
		"\n"
		"      %08X\n"
		"      %08X\n"
		"\n",
		func,
		file, line,
		_errno,
		_errparam
	);
	raise(SIGABRT);
}


void _sb_error_fatal(const char *file, const char *func, const int line, sb_error_t _errno) {
	_sb_error_fatal_ex(file, func, line, _errno, 0);
}


void _sb_error_print() {
	#define __PRINTERR(ec,str) printf("Error #"ec" = "str)
	switch (__sb_errno) {
		case SB_ERROR_SUCCESS:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_SUCCESS), "No error occured.");
			break;
		case SB_ERROR_NULL_PTR:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_NULL_PTR), "Null pointer specified.");
			break;
		case SB_ERROR_PARAM_INVALID:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_PARAM_INVALID), "Invalid parameter specified.");
			break;
		case SB_ERROR_PARAM_RANGE:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_PARAM_RANGE), "Specified parameter is out of range.");
			break;
		case SB_ERROR_FAILSAFE:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_FAILSAFE), "Failsafe triggered.");
			break;
		case SB_ERROR_INITIALIZATION:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_INITIALIZATION), "Initialization error.");
			break;
		case SB_ERROR_DESCRIPTOR_INVALID:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_DESCRIPTOR_INVALID), "Descriptor (rendered) invalid.");
			break;
		case SB_ERROR_VALUE_INVALID:
			__PRINTERR(SB_STRINGIFY_MACRO(SB_ERROR_VALUE_INVALID), "Invalid value found.");
			break;
		default:
			break;
	}
}
