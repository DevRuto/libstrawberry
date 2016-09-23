using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibStrawberry.Exceptions
{
	public class SbException : Exception
	{
		public SbException() : base() { }
		public SbException(string message) : base(message) { }
	}
}
