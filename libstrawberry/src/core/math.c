#include "rcsid.h"
RCSID("math.c", "0.1", "1", "2016-07-29");

#include "math.h"
#include <math.h>


size_t sb_math_round_block(size_t blocksize, size_t havesize) {
	return (size_t)(ceil((havesize / (double)blocksize)) * blocksize);
}
