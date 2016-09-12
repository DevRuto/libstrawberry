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

#define __FILE_LOCAL__						"core/time.c"

//#define __SB_DONT_NEED_INTRINSICS			// Line added for the sake of consistency.

#include "./time.h"

#include <time.h>

#include "bits.h"


IDENTID(__FILE_LOCAL__, "0.2", "1", "2016-09-12");


uint64_t sb_time_tsc() {
#if SB_HAVE_INTRINSICS
	return __rdtsc();
#else
	uint32_t hi, lo;
	asm volatile ("rdtscp\n"
				  "movl %%edx, %0\n"
				  "movl %%eax, %1\n"
				  "cpuid"
				  : "=r"(hi), "=r"(lo)
				  :
				  : "%rax", "%rbx", "%rcx", "%rdx");
	return (SB_32M64(hi, lo));
#endif
}


uint64_t sb_time_nsec() {
#if (SB_PLATFORM != SB_PLATFORM_ID_WINDOWS)
	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
		return (ts.tv_sec * 1000000000) + ts.tv_nsec;
	}
	return 0;
#else
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return ((((uint64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10) - 0x295E9648864000);
#endif
}


void sb_time_sleep_nsec(uint64_t nsec) {
#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
	uint64_t s = (nsec / 1000000);
	Sleep((s ? s : 1));
#else
	struct timespec ts;
	ts.tv_sec = (nsec / 1000000000);
	ts.tv_nsec = (nsec - (ts.tv_sec * 1000000000));
	while (nanosleep(&ts, &ts) == -1);
#endif
}
