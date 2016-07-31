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
