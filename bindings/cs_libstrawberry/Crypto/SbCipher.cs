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

namespace LibStrawberry.Crypto {
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_crypto_cipher_ctx_t {
		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr data;

		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr blockmode;

		[MarshalAs(UnmanagedType.U2)]
		internal ushort cipher;

		[MarshalAs(UnmanagedType.U1)]
		internal byte padding;

		[MarshalAs(UnmanagedType.U1)]
		internal byte flags;
	}

	public enum SbCipherAlgorithm : ushort {
		Unspecified = 0,
		Rijndael = 1,
		Salsa20 = 2,
		Rabbit = 3
	}

	public enum SbCipherPaddingAlgorithm : byte {
		Default = 0,
		Zero = 1,
		PKCS7 = 2,
		ISO979712 = 3
	}

	public enum SbCipherFlags : byte {
		Unspecified = 0
	}

	public class SbCipher : IDisposable {
		public SbCipherAlgorithm Algorithm {
			get {
				return (SbCipherAlgorithm)ctx.cipher;
			}
		}

		public SbCipherPaddingAlgorithm PaddingAlgorithm {
			get {
				return (SbCipherPaddingAlgorithm)ctx.padding;
			}
		}

		public SbCipherFlags Flags {
			get {
				return (SbCipherFlags)ctx.flags;
			}
		}

		private sb_crypto_cipher_ctx_t ctx = new sb_crypto_cipher_ctx_t();

		public SbCipher(SbCipherAlgorithm algorithm, SbCipherPaddingAlgorithm padding, SbCipherFlags flags, ushort bits, byte[] key) {
			if (bits == 0 || (bits & 7) != 0) {
				throw new SbException(SbExceptionType.InvalidSize);
			}
			if (key == null || key.Length != (bits / 8)) {
				throw new SbException(SbExceptionType.InvalidKey);
			}
			if (algorithm == SbCipherAlgorithm.Unspecified) {
				throw new ArgumentException();
			}
			if (padding == SbCipherPaddingAlgorithm.Default) {
				padding = SbCipherPaddingAlgorithm.ISO979712;
			}
			if (NativeMethods.sb_crypto_cipher_init(ref ctx, (ushort)algorithm, (byte)padding, (byte)flags, bits, key) != 1) {
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
			if (NativeMethods.sb_crypto_cipher_clear(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Disposal) { DeemedFatal = true };
			}
		}

		public void Dispose() {
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}

		#endregion

		public bool Reset() {
			if (NativeMethods.sb_crypto_cipher_reset(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		// TODO: blockmode

		public ulong EncryptSize(ulong size) {
			return (ulong)NativeMethods.sb_crypto_cipher_encrypt_size(ref ctx, (UIntPtr)size);
		}

		public ulong DecryptSize(byte[] data, ulong size) {
			return (ulong)NativeMethods.sb_crypto_cipher_decrypt_size(ref ctx, data, (UIntPtr)size);
		}

		public byte[] Encrypt(byte[] _in) {
			if (_in == null) {
				throw new ArgumentNullException();
			}
			byte[] buffer = new byte[this.EncryptSize((ulong)_in.Length)];
			if (NativeMethods.sb_crypto_cipher_encrypt(ref ctx, buffer, _in, (UIntPtr)_in.Length) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return buffer;
		}

		public byte[] Decrypt(byte[] _in, out ulong size) {
			if (_in == null) {
				throw new ArgumentNullException();
			}
			UIntPtr poff = UIntPtr.Zero;
			byte[] buffer = new byte[_in.Length];
			if (NativeMethods.sb_crypto_cipher_decrypt(ref ctx, buffer, _in, (UIntPtr)_in.Length, poff) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					size = 0;
					return null;
				}
			}
			size = (ulong)poff;
			return buffer;
		}
	}
}
