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

using LibStrawberry.BindingBase;

namespace LibStrawberry.Crypto {
	public static class SbRandom {
		public static ushort GetUShort() {
			return NativeMethods.sb_random16();
		}

		public static uint GetUInt() {
			return NativeMethods.sb_random32();
		}

		public static ulong GetULong() {
			return NativeMethods.sb_random64();
		}

		public static byte[] GetBytes(uint count) {
			byte[] b = new byte[count];

			uint r, i;
			for (i = 0; count > 3; count -= 4, i += 4) {
				r = SbRandom.GetUInt();
				b[i] = (byte)((r >> 24) & 0xFF);
				b[i + 1] = (byte)((r >> 16) & 0xFF);
				b[i + 2] = (byte)((r >> 8) & 0xFF);
				b[i + 3] = (byte)((r) & 0xFF);
			}
			if (count > 0) {
				r = SbRandom.GetUInt();
				byte sm = 0;
				for (; count > 0; --count, ++i) {
					b[i] = (byte)(r >> (8 * (4 - ++sm)));
				}
			}

			return b;
		}
	}
}
