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

#include "./cli.h"

#include "./bits.h"

#include <stdio.h>


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-22");


void sb_print(const char *msg) {
	if (!msg) {
		return;
	}
	puts(msg);
}


void sb_cprint(const char *msg, uint8_t color) {
	if (!msg) {
		return;
	}
#ifdef SB_CLI_COLORS
	const char colorcodes[8] = "01234567";
	char ansi[8] = "\x1b[37;1m\0";
	ansi[3] = colorcodes[(color & 7)];
	if (!SB_FLAG(color, SB_COLOR_BRIGHT)) {
		ansi[4] = 'm';
		ansi[5] = 0;
	}
	printf("%s%s\x1b[0m\n", ansi, msg);
#else
	puts(msg);
#endif
}
