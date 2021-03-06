/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */


#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/SearchPayload.h>

namespace Swift {
	class PayloadSerializerCollection;

	class SWIFTEN_API SearchPayloadSerializer : public GenericPayloadSerializer<SearchPayload> {
		public:
			SearchPayloadSerializer();

			virtual std::string serializePayload(boost::shared_ptr<SearchPayload>)  const;
	};
}
