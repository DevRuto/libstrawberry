#include "core/identid.h"
IDENTID("dllmain.c", "0.1", "1", "2016-07-29");

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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