using LibStrawberry.BindingBase;

namespace LibStrawberry.Crypto
{
	public static class SbSeedgen
	{
		public static ulong GetULong(ulong noise) {
			return Imports.sb_seedgen(noise);
		}
	}
}
