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

#define __FILE_LOCAL__						"crypto/random.c"

#define __SB_DONT_NEED_INTRINSICS

#include "./random.h"
#include "prng/isaac.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-09-10");


static sb_crypto_prng_isaac_ctx_t __isaac;
static sb_bool_t __init = sb_false;

#define __INIT_FUN()																\
	if (!__init) {																	\
		sb_crypto_prng_isaac_init_ex(&__isaac, sb_false, (uint64_t)sb_random32);	\
		__init = sb_true;															\
	}


uint16_t sb_random16() {
	return (sb_random32() & 0xFFFF);
}


uint32_t sb_random32() {
	__INIT_FUN();
	return sb_crypto_prng_isaac(&__isaac);
}


uint64_t sb_random64() {
	__INIT_FUN();
	return (((uint64_t)sb_crypto_prng_isaac(&__isaac) << 32) | sb_crypto_prng_isaac(&__isaac));
}
