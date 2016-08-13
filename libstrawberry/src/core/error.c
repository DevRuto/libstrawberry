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

#include "identid.h"
IDENTID("error.c", "0.1", "1", "2016-07-29");

#include <stdint.h>
#include <stdio.h>
#include <signal.h>

#include "../core/error.h"


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
