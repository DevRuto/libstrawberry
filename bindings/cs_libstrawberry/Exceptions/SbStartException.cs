using System;

namespace LibStrawberry.Exceptions
{
	public class SbStartException : Exception
	{
		public SbStartException() : base() { }
		public SbStartException(string message) : base(message) { }
	}
}
