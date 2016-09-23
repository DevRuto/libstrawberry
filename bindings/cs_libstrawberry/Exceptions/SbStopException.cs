using System;

namespace LibStrawberry.Exceptions
{
	public class SbStopException : Exception
	{
		public SbStopException() : base() { }
		public SbStopException(string message) : base(message) { }
	}
}
