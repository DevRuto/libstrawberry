/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

#ifndef __SB_CORE_STDINCL_H
#define __SB_CORE_STDINCL_H


#include <stdint.h>
#include <stddef.h>

#include "./platform.h"
#include "./identid.h"
#include "./sbapi.h"

#include "./types/bool.h"


#define SB_VERSION_MAJOR					0
#define SB_VERSION_MINOR					1
#define SB_VERSION							((SB_VERSION_MAJOR << 16) | (SB_VERSION_MINOR << 8) | SB_DEBUG)
#define SB_VERSION_STRING					"libstrawberry "SB_STRINGIFY_MACRO(SB_VERSION_MAJOR)"."SB_STRINGIFY_MACRO(SB_VERSION_MINOR)" ("IDENTID_CODENAME", "SB_CHANNEL_STR") "__DATE__" "__TIME__


// Compile-time build information.
const char* sb_platform();
const char* sb_version();
const char* sb_version_full();


#endif
