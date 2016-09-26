using System;
using System.Linq;
using LibStrawberry.Crypto.KeyExchange;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace cs_libstrawberry_unit_tests
{
	[TestClass]
	public class CryptoKeyExchange
	{
		private bool TestDH(ushort bits) {
			try {
				using (SbDiffieHellman alice = new SbDiffieHellman(bits), bob = new SbDiffieHellman(bits)) {
					if (!alice.GenerateBase()) {
						return false;
					}
					if (!alice.GenerateKeys()) {
						return false;
					}

					if (!SbDiffieHellman.CopyBase(bob, alice)) {
						return false;
					}
					if (!bob.GenerateKeys()) {
						return false;
					}

					ushort
						alice_size = alice.Size,
						bob_size = bob.Size,
						size = alice_size;

					if (alice_size == 0 || bob_size != alice_size) {
						return false;
					}

					byte[]
						alice_buffer = alice.ExportPublic(),
						bob_buffer = bob.ExportPublic();

					if (!alice.GenerateSecret(bob_buffer)) {
						return false;
					}
					if (!bob.GenerateSecret(alice_buffer)) {
						return false;
					}

					if ((alice_buffer = alice.ExportSecret()) == null) {
						return false;
					}
					if ((bob_buffer = bob.ExportSecret()) == null) {
						return false;
					}

					return Enumerable.SequenceEqual(alice_buffer, bob_buffer);
				}
			} catch {
				return false;
			}
		}

		[TestMethod]
		public void DiffieHellman256() {
			Assert.IsTrue(TestDH(256));
		}

		[TestMethod]
		public void DiffieHellman512() {
			Assert.IsTrue(TestDH(512));
		}

		[TestMethod]
		public void DiffieHellman666() {
			Assert.IsFalse(TestDH(666));
		}

		[TestMethod]
		public void DiffieHellman1024() {
			Assert.IsTrue(TestDH(1024));
		}

		[TestMethod]
		public void DiffieHellman2048() {
			Assert.IsTrue(TestDH(2048));
		}
	}
}
