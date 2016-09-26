using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibStrawberry.BindingBase;

namespace LibStrawberry.Crypto
{
	public static class SbRandom
	{
		public static ushort GetUShort() {
			return Imports.sb_random16();
		}

		public static uint GetUInt() {
			return Imports.sb_random32();
		}

		public static ulong GetULong() {
			return Imports.sb_random64();
		}

		public static byte[] GetBytes(uint count) {
			byte[] b = new byte[count];

			uint r, i;
			for (i = 0; count > 3; count -= 4, i += 4) {
				r = SbRandom.GetUInt();
				b[i    ] = (byte)((r >> 24) & 0xFF);
				b[i + 1] = (byte)((r >> 16) & 0xFF);
				b[i + 2] = (byte)((r >>  8) & 0xFF);
				b[i + 3] = (byte)((r      ) & 0xFF);
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
