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
using System.Runtime.InteropServices;

using LibStrawberry.BindingBase;

namespace LibStrawberry.Networking {
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_socket_ctx_t {
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
	public enum SbSocketFlag : uint {
		Unspecified = 0x00000000,
		Server = 0x00000001,
		Exited = 0x00000002,
		UDP = 0x00000004,
		Accepted	= 0x00000008
	}

	public class SbSocket : IDisposable {
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
				if (!NativeMethods.sb_socket_init(ref ctx, node, (uint)flags)) {
					throw new SbException(SbExceptionType.Initialization);
				}
			}
		}

		public SbSocket(ulong fd, SbSocketFlag flags = 0) {
			if (!NativeMethods.sb_socket_fromfd(ref ctx, fd, (uint)flags)) {
				throw new SbException(SbExceptionType.Initialization);
			}
		}

		private SbSocket(ref sb_socket_ctx_t ctx) {
			this.ctx.fd = ctx.fd;
			this.ctx.addrinfo = ctx.addrinfo;
			this.ctx.selected = ctx.selected;
			this.ctx.flags = ctx.flags;
		}

		#region IDisposable

		private bool __disposed = false;

		protected virtual void Dispose(bool disposing) {
			if (this.__disposed) {
				return;
			} else {
				this.__disposed = true;
			}
			if (disposing) {
				// Free managed objects here.
			}
			if (!NativeMethods.sb_socket_clear(ref ctx)) {
				throw new SbException(SbExceptionType.Disposal) { DeemedFatal = true };
			}
		}

		public void Dispose() {
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}

		#endregion

		public void Start(ushort port) {
			if (port == 0) {
				throw new ArgumentOutOfRangeException();
			}
			if (this.Node == null) {
				throw new SbException();
			}
			this.Port = port;
			if (!NativeMethods.sb_socket_start(ref ctx, port)) {
				throw new SbException(SbExceptionType.Generic);
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
			if (!NativeMethods.sb_socket_init(ref ctx, node, (uint)this.Flags)) {
				throw new SbException(SbExceptionType.Initialization);
			}
			this.Port = port;
			if (!NativeMethods.sb_socket_start(ref ctx, port)) {
				throw new SbException(SbExceptionType.Generic);
			}
		}

		public void Stop() {
			if (!NativeMethods.sb_socket_stop(ref ctx)) {
				throw new SbException(SbExceptionType.Generic);
			} 
		}

		public SbSocket Accept() {
			sb_socket_ctx_t nctx = new sb_socket_ctx_t();
			if (!NativeMethods.sb_socket_accept(ref ctx, ref nctx, UIntPtr.Zero, UIntPtr.Zero)) {
				throw new SbException();
			}
			return new SbSocket(ref nctx);
		}

		public long Write(byte[] data) {
			if (data == null) {
				throw new ArgumentNullException();
			}
			return (long)NativeMethods.sb_socket_write(ref ctx, data, (IntPtr)data.Length);
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
			return (long)NativeMethods.sb_socket_read(ref ctx, buffer, (IntPtr)size);
		}
	}
}
