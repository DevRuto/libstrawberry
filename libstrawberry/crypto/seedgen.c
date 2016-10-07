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

#define __FILE_LOCAL__						"crypto/seedgen.c"

#if !defined(SB_EXCLUDE_CRYPTO_RANDOM) && !defined(SB_EXCLUDE_CRYPTO_SEEDGEN)

#include "./seedgen.h"

#include "../core/time.h"
#include "../core/bits.h"
#include "./random.h"

#include "../core/poison.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-14");


uint64_t sb_crypto_seedgen(uint64_t noise) {
	uint64_t tsc = sb_time_tsc();
	return ((tsc + ((SB_ROTR64(sb_time_nsec(), (tsc & 7))) ^ noise)) & ~sb_random64());
}

#else
#	ifdef REPORT_EXCLUSION
#		pragma message("Excluded: "__FILE_LOCAL__)
#	endif
#endif
