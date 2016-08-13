/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU General Public License as published by         **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU General Public License for more details.                                 **
**                                                                               **
**  You should have received a copy of the GNU General Public License            **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CRYPTO_PADDING_PKCS7_H
#define __SB_CRYPTO_PADDING_PKCS7_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"
#include "../../core/types/bool.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_crypto_pad_pkcs7_size(sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_bool_t sb_crypto_pad_pkcs7(void *out, void *in, sb_size_t blocksize, sb_size_t havesize);
	SBAPI sb_size_t sb_crypto_pad_pkcs7_offset(void *in, sb_size_t havesize);

#ifdef __cplusplus
}
#endif


#endif
