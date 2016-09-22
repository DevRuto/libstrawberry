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

#ifndef __SB_CORE_CLI_H
#define __SB_CORE_CLI_H


#include "./stdincl.h"


#define SB_COLOR_BRIGHT						128

#define SB_COLOR_DARK_GRAY					0
#define SB_COLOR_RED						1
#define SB_COLOR_GREEN						2
#define SB_COLOR_YELLOW						3
#define SB_COLOR_BLUE						4
#define SB_COLOR_MAGENTA					5
#define SB_COLOR_CYAN						6
#define SB_COLOR_WHITE						7

#define SB_COLOR_GRAY						(SB_COLOR_BRIGHT | SB_COLOR_DARK_GRAY)
#define SB_COLOR_BRIGHT_RED					(SB_COLOR_BRIGHT | SB_COLOR_RED)
#define SB_COLOR_BRIGHT_GREEN				(SB_COLOR_BRIGHT | SB_COLOR_GREEN)
#define SB_COLOR_BRIGHT_YELLOW				(SB_COLOR_BRIGHT | SB_COLOR_YELLOW)
#define SB_COLOR_BRIGHT_BLUE				(SB_COLOR_BRIGHT | SB_COLOR_BLUE)
#define SB_COLOR_BRIGHT_MAGENTA				(SB_COLOR_BRIGHT | SB_COLOR_MAGENTA)
#define SB_COLOR_BRIGHT_CYAN				(SB_COLOR_BRIGHT | SB_COLOR_CYAN)
#define SB_COLOR_BRIGHT_WHITE				(SB_COLOR_BRIGHT | SB_COLOR_WHITE)

// To avoid a war with the British.
#define SB_COLOR_DARK_GREY					SB_COLOR_DARK_GRAY
#define SB_COLOR_GREY						SB_COLOR_GRAY


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_print(const char *msg);
	SBAPI void sb_cprint(const char *msg, uint8_t color);

#ifdef __cplusplus
}
#endif


#endif
