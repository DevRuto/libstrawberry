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

#ifndef __SB_CORE_RCSID_H
#define __SB_CORE_RCSID_H


#include "platform.h"


#define IDENTID_COMPILED_BY					"dev"


#define _IDENTID(x)							static const char identid[] = x
#define IDENTID(file, version, rev, date)	_IDENTID("$Id: "file", "version":"rev" "date" "IDENTID_COMPILED_BY" "SB_FULL_PLATFORM_STRING" $")

/* template
#include "identid.h"
IDENTID("xxx.x", "X.X", "X", "XXXX-XX-XX");


*/


#endif
