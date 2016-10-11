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

using System;

using LibStrawberry.BindingBase;

namespace LibStrawberry.Core {
	public static class SbError {
		public static uint Get() {
			return NativeMethods.sb_error_get();
		}

		public static Code GetAsCode() {
			return (Code)SbError.Get();
		}

		public static uint GetParam() {
			return NativeMethods.sb_error_get_param();
		}

		public static void Print() {
			NativeMethods.sb_error_print();
		}

		[Flags]
		public enum Flags : uint
		{
			Unspecified 		= 0x00000000,
			Internal 			= 0x80000000,
			Fatal 				= 0x40000000
		}

		public enum Code : uint
		{
			Success 			= (0x00000000 | Flags.Internal),
			NullPtr				= (0x00000001 | Flags.Internal),
			ParamInvalid		= (0x00000002 | Flags.Internal),
			ParamRange			= (0x00000003 | Flags.Internal),
			Failsafe			= (0x00000004 | Flags.Internal),
			FatalUnknown		= (0x00000005 | Flags.Internal | Flags.Fatal),
			FatalOutOfMemory	= (0x00000006 | Flags.Internal | Flags.Fatal),
			FatalPtrInvalid		= (0x00000007 | Flags.Internal | Flags.Fatal),
			Initialization		= (0x00000008 | Flags.Internal),
			FatalLockFailure	= (0x00000009 | Flags.Internal | Flags.Fatal),
			DescriptorInvalid	= (0x0000000A | Flags.Internal),
			ValueInvalid		= (0x0000000B | Flags.Internal),
			EntryNotFound		= (0x0000000C | Flags.Internal),
			Functionality		= (0x0000000D | Flags.Internal),
			Cleanup				= (0x0000000E | Flags.Internal),
			SocketWrite			= (0x00000010 | Flags.Internal),
			SocketRead			= (0x00000011 | Flags.Internal),
			StateInvalid		= (0x00000012 | Flags.Internal)
		}
	}
}
