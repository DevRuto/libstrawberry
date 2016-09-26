using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibStrawberry.Core;
using LibStrawberry.Crypto;
using LibStrawberry.Networking;
using LibStrawberry.Crypto.KeyExchange;

namespace cs_test
{
	class Program
	{
		static void Main(string[] args) {
			SbDiffieHellman alice = new SbDiffieHellman(1024);
			alice.GenerateBase();
			alice.GenerateKeys();

			SbDiffieHellman bob = new SbDiffieHellman(1024);
			SbDiffieHellman.CopyBase(bob, alice);
			bob.GenerateKeys();

			ushort
				alice_size = alice.Size,
				bob_size = bob.Size,
				size = alice_size;

			if (alice_size == 0 || bob_size != alice_size) {
				return;
			}

			byte[]
				alice_buffer = alice.ExportPublic(),
				bob_buffer = bob.ExportPublic();

			alice.GenerateSecret(bob_buffer);
			bob.GenerateSecret(alice_buffer);

			alice_buffer = alice.ExportSecret();
			bob_buffer = bob.ExportSecret();

			alice.Dispose();
			bob.Dispose();

			return;

			/*byte[] rb = SbRandom.GetBytes(4096);
			string platform = SbInfo.Platform;
			string version = SbInfo.Version;
			string version_full = SbInfo.FullVersion;
			SbSocket socket = new SbSocket("192.168.2.14");
			socket.Start(6095);
			socket.Write(new byte[] { 0x01, 0x11, 0x00, 0x04, 0xDE, 0xAD, 0xBE, 0xEF });
			byte[] buffer = new byte[256];
			long read;
			if ((read = socket.Read(ref buffer, 256)) > 0) {
				socket.Stop();
			} else {
				socket.Stop();
			}*/
		}
	}
}
