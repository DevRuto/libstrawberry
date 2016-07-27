#include <stdint.h>

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