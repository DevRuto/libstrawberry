using System;
using System.Runtime.InteropServices;

namespace LibStrawberry.BindingBase
{
	internal static class Imports
	{
		/*
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		*/
		const string lib = "libstrawberry.dll";
		const CharSet cs = CharSet.Ansi;
		const CallingConvention cc = CallingConvention.Cdecl;

		static Imports() {
			try {
				System.IO.File.WriteAllBytes(Environment.CurrentDirectory + "/libgmp.dll", Properties.Resources.libgmp);
				System.IO.File.WriteAllBytes(Environment.CurrentDirectory + "/libstrawberry.dll", Properties.Resources.libstrawberry);
			} catch (Exception ex) {
				Console.WriteLine(ex.Message);
				Console.WriteLine(ex.StackTrace);
				Environment.Exit(1);
			}
		}

		#region core/error.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_error_get();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_error_get_param();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern void sb_error_print();
		#endregion
		#region networking/socket.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_init(
			ref sb_socket_ctx_t socket,
			string node,
			uint flags
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_clear(
			ref sb_socket_ctx_t socket
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_fromfd(
			ref sb_socket_ctx_t socket,
			ulong fd,
			uint flags
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_start(
			ref sb_socket_ctx_t socket,
			ushort port
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_stop(
			ref sb_socket_ctx_t socket
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_accept(
			ref sb_socket_ctx_t sock,
			ref sb_socket_ctx_t sock_out,
			UIntPtr saddr,
			UIntPtr saddrlen
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern ulong sb_socket_acceptfd(
			ref sb_socket_ctx_t sock,
			UIntPtr saddr,
			UIntPtr saddrlen
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_socket_write(
			ref sb_socket_ctx_t sock,
			[In] byte[] _in,
			IntPtr size
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_socket_read(
			ref sb_socket_ctx_t sock,
			[Out] byte[] _out,
			IntPtr size
		);
		#endregion
	}
}
