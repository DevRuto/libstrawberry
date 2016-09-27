using System;
using System.Runtime.InteropServices;
using LibStrawberry.BindingBase;
using LibStrawberry.Core;

namespace LibStrawberry.Crypto
{
	[StructLayout(LayoutKind.Sequential)]
	internal struct sb_crypto_cipher_ctx_t
	{
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

	public enum SbCipherAlgorithm : ushort
	{
		Unspecified = 0,
		Rijndael = 1,
		Salsa20 = 2,
		Rabbit = 3
	}

	public enum SbCipherPaddingAlgorithm : byte
	{
		Default = 0,
		Zero = 1,
		PKCS7 = 2,
		ISO979712 = 3
	}

	public enum SbCipherFlags : byte
	{
		Unspecified = 0
	}

	public class SbCipher : IDisposable
	{
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

		public bool Encrypt(ref byte[] _out, byte[] _in) {
			if (_out == null || _in == null) {
				throw new ArgumentNullException();
			}
			if (NativeMethods.sb_crypto_cipher_encrypt(ref ctx, _out, _in, (UIntPtr)_in.Length) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					return false;
				}
			}
			return true;
		}

		public bool Decrypt(ref byte[] _out, byte[] _in, out ulong size) {
			if (_out == null || _in == null) {
				throw new ArgumentNullException();
			}
			UIntPtr poff = UIntPtr.Zero;
			if (NativeMethods.sb_crypto_cipher_decrypt(ref ctx, _out, _in, (UIntPtr)_in.Length, poff) != 1) {
				if (SbInfo.ThrowExceptions) {
					throw new SbException(SbExceptionType.Generic);
				} else {
					size = 0;
					return false;
				}
			}
			size = (ulong)poff;
			return true;
		}
	}
}
