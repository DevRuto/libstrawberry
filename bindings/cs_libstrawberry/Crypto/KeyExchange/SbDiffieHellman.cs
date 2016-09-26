using System;
using System.Runtime.InteropServices;

using LibStrawberry.BindingBase;
using LibStrawberry.Core;
using LibStrawberry.Exceptions;

namespace LibStrawberry.Crypto.KeyExchange
{
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_crypto_diffiehellman_ctx_t
	{
		[MarshalAs(UnmanagedType.SysUInt)]
		internal UIntPtr data;

		[MarshalAs(UnmanagedType.U2)]
		internal ushort bits;
	}

	public class SbDiffieHellman : IDisposable
	{
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
			if (Imports.sb_crypto_diffiehellman_init(ref ctx, bits, ((seed != 0) ? seed : SbSeedgen.GetULong(SbRandom.GetULong()))) != 1) {
				throw new SbException(SbExceptionType.Initialization);
			}
		}

		#region IDisposable
		protected virtual void Dispose(bool disposing) {
			if (disposing) {
				// Free managed objects here.
			}
			if (Imports.sb_crypto_diffiehellman_clear(ref ctx) != 1) {
				throw new SbException(SbExceptionType.Disposal) { DeemedFatal = true };
			}
		}

		public void Dispose() {
			Dispose(true);
			GC.SuppressFinalize(this);
		}
		#endregion

		public bool GenerateBase() {
			if (Imports.sb_crypto_diffiehellman_generate_base(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Initialization);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool GenerateKeys() {
			if (Imports.sb_crypto_diffiehellman_generate_keys(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Initialization);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool Generate() {
			if (Imports.sb_crypto_diffiehellman_generate(ref ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Initialization);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool GenerateSecret(byte[] pk_bob) {
			if (Imports.sb_crypto_diffiehellman_generate_secret(ref ctx, pk_bob) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Initialization);
				} else {
					return false;
				}
			}
			return true;
		}

		public static bool CopyBase(SbDiffieHellman dst, SbDiffieHellman src) {
			if (Imports.sb_crypto_diffiehellman_copy_base(ref dst.ctx, ref src.ctx) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public static bool CopyKeys(SbDiffieHellman dst, SbDiffieHellman src) {
			if (Imports.sb_crypto_diffiehellman_copy_keys(ref dst.ctx, ref src.ctx) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_import_generator(ref ctx, generator) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_import_modulo(ref ctx, modulo) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_import_public(ref ctx, _public) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_export_generator(ref ctx, b) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_export_modulo(ref ctx, b) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_export_public(ref ctx, b) != 1) {
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
			if (Imports.sb_crypto_diffiehellman_export_secret(ref ctx, b) != 1) {
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
