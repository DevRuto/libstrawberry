using LibStrawberry.BindingBase;

namespace LibStrawberry.Core
{
	public static class SbError
	{
		public static uint Get() {
			return NativeMethods.sb_error_get();
		}

		public static uint GetParam() {
			return NativeMethods.sb_error_get_param();
		}

		public static void Print() {
			NativeMethods.sb_error_print();
		}
	}
}
