/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
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

#include "identid.h"
IDENTID("time.c", "0.1", "1", "2016-07-29");

#include <stdint.h>
#include <time.h>

#include "../core/time.h"

uint64_t sb_time_nsec() {
#if (SB_PLATFORM != SB_PLATFORM_ID_WINDOWS)
	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
		return (ts.tv_sec * 1000000000UL) + ts.tv_nsec;
	}
	return 0;
#else
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	return ((((uint64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime) / 10) - 0x295E9648864000);
#endif
}
