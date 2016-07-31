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

void sb_error_fatal_ex(sb_error_t _errno, sb_error_t _errparam) {
	printf("STRAWBERRY FATAL: %08X %08X\n", _errno, _errparam);
	raise(SIGABRT);
}

void sb_error_fatal(sb_error_t _errno) {
	sb_error_fatal_ex(_errno, 0);
}