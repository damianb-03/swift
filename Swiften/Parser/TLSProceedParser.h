/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Parser/GenericElementParser.h>
#include <Swiften/Elements/TLSProceed.h>

namespace Swift {
	class SWIFTEN_API TLSProceedParser : public GenericElementParser<TLSProceed> {
		public:
			TLSProceedParser() : GenericElementParser<TLSProceed>() {}
	};
}
