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

#ifndef __SB_CORE_MATH_H
#define __SB_CORE_MATH_H


#include <stdint.h>
#include <stddef.h>

#include "sbapi.h"


#define SB_MATH_RANGE(min, max, value)		(value % (max - min) + min)


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_size_t sb_math_round_block(sb_size_t blocksize, sb_size_t havesize);

#ifdef __cplusplus
}
#endif


#endif
