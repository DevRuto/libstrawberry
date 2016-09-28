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

namespace LibStrawberry.Crypto.KeyExchange {
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_crypto_diffiehellman_ctx_t {
		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr data;

		[MarshalAs(UnmanagedType.U2)]
		internal ushort bits;
	}

	public class SbDiffieHellman : IDisposable {
		public ushort Bits {
			get {
				return ctx.bits;
			}
		}

		public ushort Size {
			get {
				if (_size == null) {
					_size = (ushort)(this.Bits / 8);
				}
				return (ushort)_size;
			}
		}

		private ushort? _size = null;
		private sb_crypto_diffiehellman_ctx_t ctx = new sb_crypto_diffiehellman_ctx_t();

		public SbDiffieHellman(ushort bits, ulong seed = 0) {
			if (NativeMethods.sb_crypto_diffiehellman_init(ref ctx, bits, ((seed != 0) ? seed : SbSeedgen.GetULong(SbRandom.GetULong()))) != 1) {
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
			if (NativeMethods.sb_crypto_diffiehellman_clear(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Disposal) { DeemedFatal = true };
			}
		}

		public void Dispose() {
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}

		#endregion

		public bool GenerateBase() {
			if (NativeMethods.sb_crypto_diffiehellman_generate_base(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool GenerateKeys() {
			if (NativeMethods.sb_crypto_diffiehellman_generate_keys(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool Generate() {
			if (NativeMethods.sb_crypto_diffiehellman_generate(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool GenerateSecret(byte[] pk_bob) {
			if (NativeMethods.sb_crypto_diffiehellman_generate_secret(ref ctx, pk_bob) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public static bool CopyBase(SbDiffieHellman dst, SbDiffieHellman src) {
			if (NativeMethods.sb_crypto_diffiehellman_copy_base(ref dst.ctx, ref src.ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public static bool CopyKeys(SbDiffieHellman dst, SbDiffieHellman src) {
			if (NativeMethods.sb_crypto_diffiehellman_copy_keys(ref dst.ctx, ref src.ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool ImportGenerator(byte[] generator) {
			if (generator == null) {
				throw new ArgumentNullException();
			}
			if (generator.Length != this.Size) {
				throw new ArgumentException();
			}
			if (NativeMethods.sb_crypto_diffiehellman_import_generator(ref ctx, generator) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool ImportModulo(byte[] modulo) {
			if (modulo == null) {
				throw new ArgumentNullException();
			}
			if (modulo.Length != this.Size) {
				throw new ArgumentException();
			}
			if (NativeMethods.sb_crypto_diffiehellman_import_modulo(ref ctx, modulo) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool ImportPublic(byte[] _public) {
			if (_public == null) {
				throw new ArgumentNullException();
			}
			if (_public.Length != this.Size) {
				throw new ArgumentException();
			}
			if (NativeMethods.sb_crypto_diffiehellman_import_public(ref ctx, _public) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool Import(byte[] generator, byte[] modulo, byte[] _public) {
			if (generator != null) {
				if (!this.ImportGenerator(generator)) {
					return false;
				}
			}
			if (modulo != null) {
				if (!this.ImportModulo(modulo)) {
					return false;
				}
			}
			if (_public != null) {
				if (!this.ImportPublic(_public)) {
					return false;
				}
			}
			return true;
		}

		public byte[] ExportGenerator() {
			byte[] b = new byte[this.Size];
			if (NativeMethods.sb_crypto_diffiehellman_export_generator(ref ctx, b) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return b;
		}

		public byte[] ExportModulo() {
			byte[] b = new byte[this.Size];
			if (NativeMethods.sb_crypto_diffiehellman_export_modulo(ref ctx, b) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return b;
		}

		public byte[] ExportPublic() {
			byte[] b = new byte[this.Size];
			if (NativeMethods.sb_crypto_diffiehellman_export_public(ref ctx, b) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return b;
		}

		public byte[] ExportSecret() {
			byte[] b = new byte[this.Size];
			if (NativeMethods.sb_crypto_diffiehellman_export_secret(ref ctx, b) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return null;
				}
			}
			return b;
		}
	}
}
