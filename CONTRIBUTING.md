# Contributing to libstrawberry

## Guidelines
* Use tabs.
* Place **two** newlines between functions.
* Pre-increment and pre-decrement where possible, as opposed to post-incrementing/post-decrementing.
* When possible, reverse loops. Ex.:
`for (i = 10; i--;)` as opposed to `for (i = 0; i < 10; ++i)`.
* Keep error reporting in mind.
* Use "fixed" relative paths for internal includes. Ex.: ```#include "./time.h"``` as opposed to ```#include "time.h"```.
* Use **UPPERCASE** hexadecimal values. Ex.: ```0xBEEFBAAFU``` as opposed to ```0xbeefbaafu```.
* Use **UPPERCASE** type specifications for literal expressions where you use them. Ex.: ```1U``` as opposed to ```1u```.
* Specify operator precedence. Ex.: ```i = (foo + bar)``` as opposed to ```i = foo + bar```.

## File format
```
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
**    Contributed by <name>.
**
*/
\n
<define __FILE_LOCAL__>
\n
<optional feature definitions + \n>
<include own header file>
\n
<optional system includes + \n>
<optional internal includes + \n>
\n
<poison header + \n>
\n
\n
<identid macro>
\n
\n
<optional constants/variables + \n\n>
function
\n
\n
function
\n
```

## Example file (sub/dir/example.c)
```
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
**    Contributed by strawberryentrypoint.
**
*/

#define __FILE_LOCAL__                      "sub/dir/example.c"

#define SB_INTRINSICS

#include "./example.h"

#include <stdio.h>

#include "../../core/time.h"

#include "../../core/poison.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-10-05");


static uint64_t last_exec = 0;


void foo() {
    last_exec = sb_time_nsec();
}


void bar() {
    if (last_exec) {
        printf("foo() was last executed %lu nanoseconds ago.\n", (sb_time_nsec() - last_exec));
    } else {
        puts("foo() hasn't been executed yet.");
    }
}

```


