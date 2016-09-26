using System;
using System.Runtime.InteropServices;

using LibStrawberry.Crypto.KeyExchange;
using LibStrawberry.Networking;

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

		#region dllmain.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_platform();
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_version();
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_version_full();
		#endregion
		#region core/error.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_error_get();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_error_get_param();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern void sb_error_print();
		#endregion
		#region crypto/key_exchange/diffiehellman.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_init(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[In] ushort bits,
			[In] ulong seed
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_clear(
			ref sb_crypto_diffiehellman_ctx_t ctx
		);
		
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_generate_base(
			ref sb_crypto_diffiehellman_ctx_t ctx
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_generate_keys(
			ref sb_crypto_diffiehellman_ctx_t ctx
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_generate(
			ref sb_crypto_diffiehellman_ctx_t ctx
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_generate_secret(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[In] byte[] pk_bob
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_copy_base(
			ref sb_crypto_diffiehellman_ctx_t dst,
			ref sb_crypto_diffiehellman_ctx_t src
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_copy_keys(
			ref sb_crypto_diffiehellman_ctx_t dst,
			ref sb_crypto_diffiehellman_ctx_t src
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern UIntPtr sb_crypto_diffiehellman_port_size(
			ref sb_crypto_diffiehellman_ctx_t ctx
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_import_generator(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[In] byte[] _in
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_import_modulo(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[In] byte[] _in
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_import_public(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[In] byte[] _in
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_export_generator(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[Out] byte[] _out
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_export_modulo(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[Out] byte[] _out
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_export_public(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[Out] byte[] _out
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_crypto_diffiehellman_export_secret(
			ref sb_crypto_diffiehellman_ctx_t ctx,
			[Out] byte[] _out
		);
		#endregion
		#region crypto/random.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern ushort sb_random16();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_random32();

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern ulong sb_random64();
		#endregion
		#region networking/socket.c
		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_init(
			ref sb_socket_ctx_t socket,
			[In] string node,
			[In] uint flags
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_clear(
			ref sb_socket_ctx_t socket
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_fromfd(
			ref sb_socket_ctx_t socket,
			[In] ulong fd,
			[In] uint flags
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_start(
			ref sb_socket_ctx_t socket,
			[In] ushort port
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_stop(
			ref sb_socket_ctx_t socket
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern uint sb_socket_accept(
			ref sb_socket_ctx_t sock,
			ref sb_socket_ctx_t sock_out,
			[Out] UIntPtr saddr,
			[Out] UIntPtr saddrlen
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern ulong sb_socket_acceptfd(
			ref sb_socket_ctx_t sock,
			[Out] UIntPtr saddr,
			[Out] UIntPtr saddrlen
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_socket_write(
			ref sb_socket_ctx_t sock,
			[In] byte[] _in,
			[In] IntPtr size
		);

		[DllImport(lib, CharSet = cs, CallingConvention = cc)]
		internal static extern IntPtr sb_socket_read(
			ref sb_socket_ctx_t sock,
			[Out] byte[] _out,
			[In] IntPtr size
		);
		#endregion
	}
}
