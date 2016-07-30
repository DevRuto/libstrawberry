#ifndef __SB_CORE_MATH_H
#define __SB_CORE_MATH_H


#include <stdint.h>
#include <stddef.h>

#include "sbapi.h"


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI size_t sb_math_round_block(size_t blocksize, size_t havesize);

#ifdef __cplusplus
}
#endif


#endif
