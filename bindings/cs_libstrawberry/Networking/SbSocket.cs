using System;
using System.Runtime.InteropServices;

using LibStrawberry.BindingBase;
using LibStrawberry.Exceptions;

namespace LibStrawberry.Networking
{
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_socket_ctx_t
	{
		[MarshalAs(UnmanagedType.U8)]
		internal ulong fd;
		
		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr addrinfo;
		
		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr selected;

		[MarshalAs(UnmanagedType.U4)]
		internal uint flags;
	}

	[Flags]
	public enum SbSocketFlag : uint
	{
		Server		= 0x00000001,
		Exited		= 0x00000002,
		UDP			= 0x00000004,
		Accepted	= 0x00000008
	}

	public class SbSocket
	{
		public string Node { get; private set; }
		public ushort Port { get; private set; }
		public SbSocketFlag Flags {
			get {
				return (SbSocketFlag)ctx.flags;
			}
		}

		private sb_socket_ctx_t ctx = new sb_socket_ctx_t();

		public SbSocket(string node = null, SbSocketFlag flags = 0) {
			this.Node = node;
			if (node != null) {
				if (Imports.sb_socket_init(ref ctx, node, (uint)flags) != 1) {
					throw new SbException(SbExceptionType.Initialization);
				}
			}
		}

		public SbSocket(ulong fd, SbSocketFlag flags = 0) {
			if (Imports.sb_socket_fromfd(ref ctx, fd, (uint)flags) != 1) {
				throw new SbException(SbExceptionType.Initialization);
			}
		}

		private SbSocket(ref sb_socket_ctx_t ctx) {
			this.ctx.fd = ctx.fd;
			this.ctx.addrinfo = ctx.addrinfo;
			this.ctx.selected = ctx.selected;
			this.ctx.flags = ctx.flags;
		}

		internal bool Clear() {
			return (Imports.sb_socket_clear(ref ctx) == 1);
		}

		public void Start(ushort port) {
			if (port == 0) {
				throw new ArgumentOutOfRangeException();
			}
			if (this.Node == null) {
				throw new SbException();
			}
			this.Port = port;
			if (Imports.sb_socket_start(ref ctx, port) != 1) {
				throw new SbException(SbExceptionType.Start);
			}
		}

		public void Start(string node, ushort port) {
			if (port == 0) {
				throw new ArgumentOutOfRangeException();
			}
			if (node == null) {
				throw new SbException(SbExceptionType.Initialization);
			}
			this.Node = node;
			if (Imports.sb_socket_init(ref ctx, node, (uint)this.Flags) != 1) {
				throw new SbException(SbExceptionType.Initialization);
			}
			this.Port = port;
			if (Imports.sb_socket_start(ref ctx, port) != 1) {
				throw new SbException(SbExceptionType.Start);
			}
		}

		public void Stop() {
			if (Imports.sb_socket_stop(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Stop);
			} 
		}

		public SbSocket Accept() {
			sb_socket_ctx_t nctx = new sb_socket_ctx_t();
			if (Imports.sb_socket_accept(ref ctx, ref nctx, UIntPtr.Zero, UIntPtr.Zero) != 1) {
				throw new SbException();
			}
			return new SbSocket(ref nctx);
		}

		public long Write(byte[] data) {
			if (data == null) {
				throw new ArgumentNullException();
			}
			return (long)Imports.sb_socket_write(ref ctx, data, (IntPtr)data.Length);
		}

		public long Read(ref byte[] buffer, long size) {
			if (buffer == null) {
				throw new ArgumentNullException();
			}
			if (size < 0) {
				throw new ArgumentOutOfRangeException();
			}
			if (size == 0) {
				return 0;
			}
			return (long)Imports.sb_socket_read(ref ctx, buffer, (IntPtr)size);
		}
	}
}
