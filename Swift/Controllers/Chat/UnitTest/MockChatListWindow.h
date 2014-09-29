/*
 * Copyright (c) 2011-2014 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include "Swift/Controllers/UIInterfaces/ChatListWindow.h"

namespace Swift {

	class MockChatListWindow : public ChatListWindow {
		public:
			MockChatListWindow() {}
			virtual ~MockChatListWindow() {}
			void addMUCBookmark(const MUCBookmark& /*bookmark*/) {}
			void removeMUCBookmark(const MUCBookmark& /*bookmark*/) {}
			void addWhiteboardSession(const ChatListWindow::Chat& /*chat*/) {}
			void removeWhiteboardSession(const JID& /*jid*/) {}
			void setBookmarksEnabled(bool /*enabled*/) {}
			void setRecents(const std::list<ChatListWindow::Chat>& /*recents*/) {}
			void setUnreadCount(int /*unread*/) {}
			void clearBookmarks() {}
			void setOnline(bool /*isOnline*/) {}
	};

}
