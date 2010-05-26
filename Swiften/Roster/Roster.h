/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#ifndef SWIFTEN_Roster_H
#define SWIFTEN_Roster_H

#include "Swiften/Base/String.h"
#include "Swiften/JID/JID.h"
#include "Swiften/Roster/RosterItemOperation.h"
#include "Swiften/Roster/RosterFilter.h"

#include <vector>
#include <map>
#include <boost/signal.hpp>
#include <boost/shared_ptr.hpp>

namespace Swift {

class RosterItem;
class GroupRosterItem;
class ContactRosterItem;

class Roster {
	public:
		Roster(bool fullJIDMapping = false);
		~Roster();

		void addContact(const JID& jid, const String& name, const String& group);
		void removeContact(const JID& jid);
		void removeContactFromGroup(const JID& jid, const String& group);
		void applyOnItems(const RosterItemOperation& operation);
		void applyOnAllItems(const RosterItemOperation& operation);
		void applyOnItem(const RosterItemOperation& operation, const JID& jid);
		void addFilter(RosterFilter *filter) {filters_.push_back(filter);filterAll();};
		void removeFilter(RosterFilter *filter);
		GroupRosterItem* getRoot();
		std::vector<RosterFilter*> getFilters() {return filters_;};
		boost::signal<void (GroupRosterItem*)> onChildrenChanged;
		boost::signal<void (GroupRosterItem*)> onGroupAdded;
		boost::signal<void (RosterItem*)> onDataChanged;
	private:
		GroupRosterItem* getGroup(const String& groupName);
		void handleDataChanged(RosterItem* item);
		void handleChildrenChanged(GroupRosterItem* item);
		void filterGroup(GroupRosterItem* item);
		void filterContact(ContactRosterItem* contact, GroupRosterItem* group);
		void filterAll();
		GroupRosterItem* root_;
		std::vector<RosterFilter*> filters_;
		std::map<JID, std::vector<ContactRosterItem*> > itemMap_;
		bool fullJIDMapping_;
};
}

#endif
