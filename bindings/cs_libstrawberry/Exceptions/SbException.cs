using System;

namespace LibStrawberry.Exceptions
{
	public enum SbExceptionType
	{
		Generic,
		Initialization,
		Disposal,
		Start,
		Stop
	}

	public class SbException : Exception
	{
		public SbExceptionType Type { get; private set; }
		public bool DeemedFatal { get; internal set; }


		public SbException() : this(SbExceptionType.Generic) { }

		public SbException(SbExceptionType type) : base() {
			this.Type = type;
			this.DeemedFatal = false;
		}

		public SbException(SbExceptionType type, string message) : base(message) {
			this.Type = type;
			this.DeemedFatal = false;
		}
	}
}
