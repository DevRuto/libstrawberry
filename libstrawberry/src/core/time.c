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
