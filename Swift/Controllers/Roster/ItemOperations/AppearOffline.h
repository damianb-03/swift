/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swift/Controllers/Roster/ItemOperations/RosterItemOperation.h>
#include <Swift/Controllers/Roster/ContactRosterItem.h>

namespace Swift {

class RosterItem;

class AppearOffline : public RosterItemOperation {
	public:
		AppearOffline() {
		}

		virtual void operator() (RosterItem* item) const {
			ContactRosterItem* contact = dynamic_cast<ContactRosterItem*>(item);
			if (contact) {
				contact->clearPresence();
			}
		}

};

}


