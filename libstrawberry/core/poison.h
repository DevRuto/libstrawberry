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

#ifndef __SB_CORE_POISON_H
#define __SB_CORE_POISON_H


#include "./platform.h"


#if (SB_COMPILER == SB_COMPILER_ID_MSC)
//#	pragma warning (error: 4995)
#	define SB_POISON(x)						__pragma(deprecated(x))
#else
#	define SB_POISON(x)						_Pragma(SB_STRINGIFY_MACRO(GCC poison x))
#endif


SB_POISON(include);

#ifndef SB_POISON_EXCLUDE_MEMORY
	SB_POISON(malloc);
	SB_POISON(calloc);
	SB_POISON(realloc);
	SB_POISON(free);
	SB_POISON(memset);
	SB_POISON(memcpy);
	SB_POISON(memcmp);
	SB_POISON(strlen);
	SB_POISON(strcpy);
	SB_POISON(strcmp);
#endif

SB_POISON(size_t);


#if (SB_COMPILER == SB_COMPILER_ID_MSC)
#	pragma warning (disable: 4081)
#endif

SB_POISON(int);

#if (SB_COMPILER == SB_COMPILER_ID_MSC)
#	pragma warning (default: 4081)
#endif


#endif
