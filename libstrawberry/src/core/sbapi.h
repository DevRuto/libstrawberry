#ifndef __SB_CORE_SBAPI_H
#define __SB_CORE_SBAPI_H


#include "platform.h"


#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	ifdef LIBSTRAWBERRY_EXPORTS
#		define SBAPI						__declspec(dllexport)
#	else
#		define SBAPI						__declspec(dllimport)
#	endif
#else
#	define SBAPI
#endif


#endif
