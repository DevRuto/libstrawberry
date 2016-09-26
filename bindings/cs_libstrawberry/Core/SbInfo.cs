using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using LibStrawberry.BindingBase;

namespace LibStrawberry.Core
{
	public static class SbInfo
	{
		private static readonly string
			_platform = Marshal.PtrToStringAnsi(Imports.sb_platform()),
			_version = Marshal.PtrToStringAnsi(Imports.sb_version()),
			_version_full = Marshal.PtrToStringAnsi(Imports.sb_version_full());

		public static string Platform {
			get {
				return _platform;
			}
		}

		public static string Version {
			get {
				return _version;
			}
		}

		public static string FullVersion {
			get {
				return _version_full;
			}
		}

		public static bool ThrowExceptions { get; set; }

		static SbInfo() {
			ThrowExceptions = true;
		}
	}
}
