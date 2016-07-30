#include "core/identid.h"
#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
IDENTID("dllmain.c", "0.1", "1", "2016-07-29");


#include <stdio.h>


int APIENTRY DllMain(HMODULE hModule, DWORD ulCallReason, LPVOID lpReserved) {
	switch (ulCallReason) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return 1;
}


#else
IDENTID("dllmain.c", "-", "-", "excluded");
#endif
