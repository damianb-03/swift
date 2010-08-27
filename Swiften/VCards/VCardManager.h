/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/signals.hpp>
#include <set>

#include "Swiften/JID/JID.h"
#include "Swiften/Elements/VCard.h"
#include "Swiften/Elements/ErrorPayload.h"

namespace Swift {
	class JID;
	class VCardStorage;
	class IQRouter;

	class VCardManager {
		public:
			VCardManager(const JID& ownJID, IQRouter* iqRouter, VCardStorage* vcardStorage);

			VCard::ref getVCardAndRequestWhenNeeded(const JID& jid);
			void requestVCard(const JID& jid);
			void requestOwnVCard();

		public:
			/**
			 * The JID will always be bare.
			 */
			boost::signal<void (const JID&, VCard::ref)> onVCardChanged;

		private:
			void handleVCardReceived(const JID& from, VCard::ref, const boost::optional<ErrorPayload>&);

		private:
			JID ownJID;
			IQRouter* iqRouter;
			VCardStorage* storage;
			std::set<JID> requestedVCards;
	};
}
