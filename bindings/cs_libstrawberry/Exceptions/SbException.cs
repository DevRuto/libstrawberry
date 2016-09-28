/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

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
