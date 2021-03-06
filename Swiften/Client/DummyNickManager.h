/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Client/NickManager.h>

namespace Swift {
	class VCardManager;

	class DummyNickManager : public NickManager {
		public:
			std::string getOwnNick() const {
				return "";
			}

			void setOwnNick(const std::string&) {
			}
	};
}
