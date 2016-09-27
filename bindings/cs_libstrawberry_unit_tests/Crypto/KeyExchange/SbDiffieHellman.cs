using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using LibStrawberry.Crypto.KeyExchange;

namespace cs_libstrawberry_unit_tests
{
	[TestClass]
	public class SbDiffieHellman
	{
		private void TestDH(ushort bits) {
			try {
				using (LibStrawberry.Crypto.KeyExchange.SbDiffieHellman alice = new LibStrawberry.Crypto.KeyExchange.SbDiffieHellman(bits), bob = new LibStrawberry.Crypto.KeyExchange.SbDiffieHellman(bits)) {
					Assert.IsTrue(alice.GenerateBase());
					Assert.IsTrue(alice.GenerateKeys());
					
					Assert.IsTrue(LibStrawberry.Crypto.KeyExchange.SbDiffieHellman.CopyBase(bob, alice));
					Assert.IsTrue(bob.GenerateKeys());

					ushort
						alice_size = alice.Size,
						bob_size = bob.Size,
						size = alice_size;

					Assert.IsFalse(alice_size == 0 || bob_size != alice_size);

					byte[]
						alice_buffer = alice.ExportPublic(),
						bob_buffer = bob.ExportPublic();
					
					Assert.IsTrue(alice.GenerateSecret(bob_buffer));
					Assert.IsTrue(bob.GenerateSecret(alice_buffer));
					
					Assert.IsNotNull((alice_buffer = alice.ExportSecret()));
					Assert.IsNotNull((bob_buffer = bob.ExportSecret()));

					Assert.IsTrue(Enumerable.SequenceEqual(alice_buffer, bob_buffer));
				}
			} catch {
				Assert.Fail();
			}
		}

		private void TestDHFail(ushort bits) {
			try {
				using (LibStrawberry.Crypto.KeyExchange.SbDiffieHellman alice = new LibStrawberry.Crypto.KeyExchange.SbDiffieHellman(bits), bob = new LibStrawberry.Crypto.KeyExchange.SbDiffieHellman(bits)) {
					Assert.IsFalse(alice.GenerateBase());
					Assert.IsFalse(alice.GenerateKeys());

					Assert.IsFalse(LibStrawberry.Crypto.KeyExchange.SbDiffieHellman.CopyBase(bob, alice));
					Assert.IsFalse(bob.GenerateKeys());

					ushort
						alice_size = alice.Size,
						bob_size = bob.Size,
						size = alice_size;

					Assert.IsTrue(alice_size == 0 || bob_size != alice_size);

					byte[]
						alice_buffer = alice.ExportPublic(),
						bob_buffer = bob.ExportPublic();

					Assert.IsFalse(alice.GenerateSecret(bob_buffer));
					Assert.IsFalse(bob.GenerateSecret(alice_buffer));

					Assert.IsNull((alice_buffer = alice.ExportSecret()));
					Assert.IsNull((bob_buffer = bob.ExportSecret()));

					Assert.IsFalse(Enumerable.SequenceEqual(alice_buffer, bob_buffer));
				}
			} catch {
			}
		}

		[TestMethod]
		public void DiffieHellman256() {
			TestDH(256);
		}

		[TestMethod]
		public void DiffieHellman512() {
			TestDH(512);
		}

		[TestMethod]
		public void DiffieHellman666() {
			TestDHFail(666);
		}

		[TestMethod]
		public void DiffieHellman1024() {
			TestDH(1024);
		}

		[TestMethod]
		public void DiffieHellman2048() {
			TestDH(2048);
		}
	}
}
