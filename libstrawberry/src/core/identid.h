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
