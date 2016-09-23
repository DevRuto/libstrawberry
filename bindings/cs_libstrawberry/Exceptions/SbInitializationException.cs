using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibStrawberry.Exceptions
{
	public class SbInitializationException : Exception {
		public SbInitializationException() : base() { }
		public SbInitializationException(string message) : base(message) { }
	}
}
