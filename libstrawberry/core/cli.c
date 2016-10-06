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

#define __FILE_LOCAL__						"core/cli.c"

#if !defined(SB_EXCLUDE_CORE_CLI)

#define SB_POISON_EXCLUDE_MEMORY

#include "./cli.h"

#include "./bits.h"
#include "./memory.h"

#include <stdio.h>

#include "./poison.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-22");


void sb_print(const char *msg) {
	if (!msg) {
		return;
	}
	fputs(msg, stdout);
}


void sb_println(const char *msg) {
	if (!msg) {
		return;
	}
	puts(msg);
}


static void sb_cprint_ex(const char *msg, uint8_t color, sb_bool_t newline) {
	if (!msg) {
		return;
	}
#ifdef SB_CLI_COLORS
	sb_size_t sz0 = 7, sz1 = sb_strlen(msg);
	char aecc[7] = "\x1B[37;1m";
	aecc[3] = (0x30 | (color & 7));
	if (!SB_FLAG(color, SB_COLOR_BRIGHT)) {
		aecc[4] = 'm';
		sz0 = 5;
	}
	SB_MEM_BUFFER_ALLOC(char, buffer, (sz0 + sz1 + 4 + 1));
	char *bp = buffer;
	sb_memcpy(bp, aecc, sz0);
	sb_strcpy((bp = (bp + sz0)), msg);
	sb_strcpy((bp = (bp + sz1)), "\x1B[0m");
	*(bp + 4) = 0;
	if (!newline) {
		fputs(buffer, stdout);
	} else {
		puts(buffer);
	}
	SB_MEM_BUFFER_FREE(buffer);
#else
	if (!newline) {
		fputs(msg, stdout);
	} else {
		puts(msg);
	}
#endif
}


void sb_cprint(const char *msg, uint8_t color) {
	sb_cprint_ex(msg, color, sb_false);
}


void sb_cprintln(const char *msg, uint8_t color) {
	sb_cprint_ex(msg, color, sb_true);
}

#else
#	ifdef REPORT_EXCLUSION
#		pragma message("Excluded: "__FILE_LOCAL__)
#	endif
#endif
