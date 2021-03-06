/*
 * Copyright (c) 2011-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/MUCDestroyPayload.h>

namespace Swift {
	class PayloadSerializerCollection;
	class SWIFTEN_API MUCDestroyPayloadSerializer : public GenericPayloadSerializer<MUCDestroyPayload> {
		public:
			MUCDestroyPayloadSerializer();
			virtual std::string serializePayload(boost::shared_ptr<MUCDestroyPayload> version)  const;
	};
}

