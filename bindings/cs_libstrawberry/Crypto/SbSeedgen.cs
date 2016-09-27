using LibStrawberry.BindingBase;

namespace LibStrawberry.Crypto
{
	public static class SbSeedgen
	{
		public static ulong GetULong(ulong noise) {
			return NativeMethods.sb_seedgen(noise);
		}
	}
}
