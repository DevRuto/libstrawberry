#ifndef STDINCL_H
#define STDINCL_H


#include <stdio.h>

#include "../../libstrawberry/core/types/bool.h"
#include "../../libstrawberry/core/error.h"
#include "../../libstrawberry/core/memory.h"

//#undef CONCLUSIONS_ONLY

#ifndef CONCLUSIONS_ONLY
#	define status(name, desc, s)				puts(s" "name": "desc)
#else
#	define status(name, desc, s)
#endif
#define status_passed						"PASSED  "
#define status_failed						"FAILED !"
#define status_info							" INFO   "


#endif
