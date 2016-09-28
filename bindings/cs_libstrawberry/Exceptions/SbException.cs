using System;
using System.Runtime.Serialization;
using System.Security.Permissions;

namespace LibStrawberry {
	public enum SbExceptionType : byte {
		Unspecified = 0,
		Generic = 1,
		Initialization = 2,
		Disposal = 3,
		InvalidSize = 4,
		InvalidKey = 5,
		InvalidIV = 6
	}

	[Serializable]
	public class SbException : Exception {
		public SbExceptionType Type { get; private set; }

		public bool DeemedFatal { get; internal set; }


		public SbException() : this(SbExceptionType.Generic) {
		}

		public SbException(SbExceptionType type) : base() {
			this.Type = type;
			this.DeemedFatal = false;
		}

		protected SbException(SerializationInfo info, StreamingContext context) : base(info, context) {
			if (info == null) {
				throw new ArgumentNullException();
			}
			this.Type = (SbExceptionType)info.GetValue("Type", typeof(SbExceptionType));
			this.DeemedFatal = (bool)info.GetValue("DeemedFatal", typeof(bool));
		}

		public SbException(SbExceptionType type, string message) : base(message) {
			this.Type = type;
			this.DeemedFatal = false;
		}

		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.SerializationFormatter)]
		new public virtual void GetObjectData(SerializationInfo info, StreamingContext context) {
			if (info == null) {
				throw new ArgumentNullException();
			}
			base.GetObjectData(info, context);
			info.AddValue("Type", this.Type, typeof(SbExceptionType));
			info.AddValue("DeemedFatal", this.DeemedFatal, typeof(bool));
		}
	}
}
