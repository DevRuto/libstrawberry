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
using LibStrawberry.Core;

namespace LibStrawberry.Crypto.Hashing {
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_crypto_ripemd160_ctx_t {
		[MarshalAs(UnmanagedType.U4)]
		internal uint data1;

		[MarshalAs(UnmanagedType.U4)]
		internal uint data2;

		[MarshalAs(UnmanagedType.U4)]
		internal uint data3;

		[MarshalAs(UnmanagedType.U4)]
		internal uint data4;

		[MarshalAs(UnmanagedType.U4)]
		internal uint data5;
	}

	public class SbRIPEMD160 : IDisposable {
		private sb_crypto_ripemd160_ctx_t ctx = new sb_crypto_ripemd160_ctx_t();

		public SbRIPEMD160() {
			if (NativeMethods.sb_crypto_ripemd160_init(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Initialization);
			}
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
			if (NativeMethods.sb_crypto_ripemd160_clear(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Disposal) { DeemedFatal = true };
			}
		}

		public void Dispose() {
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}

		#endregion

		public bool Update(byte[] data) {
			if (data == null) {
				throw new ArgumentNullException();
			}
			if (data.Length != 64) {
				throw new ArgumentException();
			}
			if (NativeMethods.sb_crypto_ripemd160_update(ref ctx, data) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool Finish(byte[] data) {
			if (data == null) {
				throw new ArgumentNullException();
			}
			if (data.Length > 64) {
				throw new ArgumentException();
			}
			if (NativeMethods.sb_crypto_ripemd160_finish(ref ctx, data, (UIntPtr)data.Length) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public byte[] GetDigest() {
			byte[] digest = new byte[20];
			if (NativeMethods.sb_crypto_ripemd160_get_digest(ref ctx, digest) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return digest;
		}

		public static byte[] GetDigest(byte[] data) {
			using (SbRIPEMD160 md = new SbRIPEMD160()) {
				uint i = 0, length = (uint)data.Length;
				byte[] buffer = null;
				if (length > 63) {
					buffer = new byte[64];
					for (i = 0; length > 63; length -= 64, i += 64) {
						Array.Copy(data, i, buffer, 0, 64);
						if (!md.Update(buffer)) {
							if (SbInfo.ThrowExceptions) {
								throw new SbException(SbExceptionType.Generic);
							} else {
								return null;
							}
						}
					}
				}
				if (length > 0) {
					buffer = new byte[length];
					Array.Copy(data, i, buffer, 0, length);
					if (!md.Finish(buffer)) {
						if (SbInfo.ThrowExceptions) {
							throw new SbException(SbExceptionType.Generic);
						} else {
							return null;
						}
					}
				}
				return md.GetDigest();
			}
		}
	}
}

