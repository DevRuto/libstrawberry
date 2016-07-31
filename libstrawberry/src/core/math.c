#include "identid.h"
IDENTID("math.c", "0.1", "1", "2016-07-29");

#include <math.h>
#include "math.h"


sb_size_t sb_math_round_block(sb_size_t blocksize, sb_size_t havesize) {
	return (sb_size_t)(ceil((havesize / (double)blocksize)) * blocksize);
}
