/**********************************************************************************
**
**  Copyright 2016 "strawberryentrypoint"
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU Lesser General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU Lesser General Public License for more details.                          **
**                                                                               **
**  You should have received a copy of the GNU Lesser General Public License     **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CRYPTO_HASHING_SHA512_H
#define __SB_CRYPTO_HASHING_SHA512_H


#include <stdint.h>
#include <stddef.h>

#include "../../core/sbapi.h"


typedef struct sb_crypto_sha512_ctx {
	void *todo;
	// TODO
} sb_crypto_sha512_ctx_t;


#endif
