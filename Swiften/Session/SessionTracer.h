/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <string>

#include <Swiften/Base/API.h>
#include <Swiften/Session/Session.h>
#include <Swiften/Base/SafeByteArray.h>

namespace Swift {
	class SWIFTEN_API SessionTracer {
		public:
			SessionTracer(boost::shared_ptr<Session> session);

		private:
			void printData(char direction, const SafeByteArray& data);

			boost::shared_ptr<Session> session;
	};
}
