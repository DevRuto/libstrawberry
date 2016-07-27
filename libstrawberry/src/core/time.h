#ifndef SB_CORE_TIME_H
#define SB_CORE_TIME_H


#include <stdint.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "sbapi.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI uint64_t sb_time_nsec();

#ifdef __cplusplus
}
#endif


#endif
