/*
 * Copyright (c) 2011-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <vector>

#include <Swiften/Base/API.h>
#include <Swiften/JID/JID.h>
#include <Swiften/Elements/Payload.h>

namespace Swift {
	class SWIFTEN_API BlockListPayload : public Payload {
		public:
			BlockListPayload(const std::vector<JID>& items = std::vector<JID>()) : items(items) {
			}

			void addItem(const JID& item) {
				items.push_back(item);
			}

			const std::vector<JID>& getItems() const {
				return items;
			}

		private:
			std::vector<JID> items;
	};
}
