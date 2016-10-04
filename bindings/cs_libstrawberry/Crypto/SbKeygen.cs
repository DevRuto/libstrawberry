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
using LibStrawberry.Core;

namespace LibStrawberry.Crypto {
	public static class SbKeygen {
		public static byte[] GetBytes(uint outsize, byte[] input) {
			if (outsize == 0) {
				return new byte[0] { };
			}
			if (input == null) {
				throw new ArgumentNullException();
			}
			if (input.Length < outsize) {
				throw new ArgumentException();
			}
			byte[] buffer = new byte[outsize];
			if (NativeMethods.sb_crypto_keygen(buffer, (UIntPtr)outsize, input, (UIntPtr)input.Length) != 1) {
				buffer = null;
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			} else {
				return buffer;
			}
		}
	}
}
