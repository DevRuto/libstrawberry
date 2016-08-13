/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU General Public License as published by         **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU General Public License for more details.                                 **
**                                                                               **
**  You should have received a copy of the GNU General Public License            **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

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
