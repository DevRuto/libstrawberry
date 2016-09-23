using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibStrawberry;

namespace cs_test
{
	class Program
	{
		static void Main(string[] args) {
			SbSocket socket = new SbSocket("192.168.2.15");
			socket.Start(6095);
			socket.Write(new byte[] { 0x01, 0x11, 0x00, 0x04, 0xDE, 0xAD, 0xBE, 0xEF });
			byte[] buffer = new byte[256];
			long read;
			if ((read = socket.Read(ref buffer, 256)) > 0) {
				socket.Stop();
			} else {
				socket.Stop();
			}
		}
	}
}
