#ifndef _SB_CORE_RCSID_H
#define _SB_CORE_RCSID_H


#include "platform.h"


#define RCSID_COMPILED_BY					"dev1"


#define _RCSID(x)							static const char rcsid[] = x
#define RCSID(file, version, rev, date)		_RCSID("$Id: "file", "version":"rev" "date" "RCSID_COMPILED_BY" "SB_FULL_PLATFORM_STRING" $")

/* template
#include "rcsid.h"
RCSID("xxx.x", "X.X", "X", "XXXX-XX-XX");


*/


#endif
