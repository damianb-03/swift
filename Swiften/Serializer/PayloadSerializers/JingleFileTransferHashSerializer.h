/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */


#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/JingleFileTransferHash.h>

namespace Swift {
	class PayloadSerializerCollection;
	class XMLElement;
	
	class SWIFTEN_API JingleFileTransferHashSerializer : public GenericPayloadSerializer<JingleFileTransferHash> {
		public:
			JingleFileTransferHashSerializer();
			
			virtual std::string serializePayload(boost::shared_ptr<JingleFileTransferHash>)  const;
	};
}
