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

#define __FILE_LOCAL__						"dllmain.c"

#define SB_INTRINSICS

#include "./core/stdincl.h"

#include "./core/time.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-30");


const char* sb_platform() {
	return SB_FULL_PLATFORM_STRING;
}

const char* sb_version() {
	return SB_VERSION_STRING;
}

const char* sb_version_full() {
	return SB_VERSION_STRING" "SB_FULL_PLATFORM_STRING;
}

const char* sb_compiler() {
	return SB_COMPILER_STRING;
}

const char* sb_compiler_full() {
	return SB_COMPILER_STRING_FULL;
}

const char* sb_compile_date() {
	return __DATE__;
}

const char* sb_compile_time() {
	return __TIME__;
}


static void __sb_const() {
	return;
}


#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
int APIENTRY DllMain(HMODULE hModule, DWORD ulCallReason, LPVOID lpReserved) {
	switch (ulCallReason) {
		case DLL_PROCESS_ATTACH:
			__sb_const();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return 1;
}
#else
static void __attribute__ ((constructor)) __sb_constructor() {
	__sb_const();
}
#endif
