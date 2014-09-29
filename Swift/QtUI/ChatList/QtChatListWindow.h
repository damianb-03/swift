/*
 * Copyright (c) 2010-2014 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <QTreeView>

#include "Swift/Controllers/UIInterfaces/ChatListWindow.h"
#include "Swift/Controllers/UIEvents/UIEventStream.h"
#include "Swift/QtUI/ChatList/ChatListModel.h"
#include "Swift/QtUI/ChatList/ChatListDelegate.h"

namespace Swift {
	class SettingsProvider;
	class QtChatListWindow : public QTreeView, public ChatListWindow {
		Q_OBJECT
		public:
			QtChatListWindow(UIEventStream *uiEventStream, SettingsProvider* settings, QWidget* parent = NULL);
			virtual ~QtChatListWindow();
			void addMUCBookmark(const MUCBookmark& bookmark);
			void removeMUCBookmark(const MUCBookmark& bookmark);
			void addWhiteboardSession(const ChatListWindow::Chat& chat);
			void removeWhiteboardSession(const JID& jid);
			void setBookmarksEnabled(bool enabled);
			void setRecents(const std::list<ChatListWindow::Chat>& recents);
			void setUnreadCount(int unread);
			void clearBookmarks();
			virtual void setOnline(bool isOnline);

		signals:
			void onCountUpdated(int count);
		private slots:
			void handleItemActivated(const QModelIndex&);
			void handleAddBookmark();
			void handleEditBookmark();
			void handleRemoveBookmark();
			void handleAddBookmarkFromRecents();
			void handleClicked(const QModelIndex& index);
			void handleSettingChanged(const std::string& setting);
			void handleClearRecentsRequested();

		protected:
			void dragEnterEvent(QDragEnterEvent* event);
			void contextMenuEvent(QContextMenuEvent* event);

		private:
			void setupContextMenus();
			bool bookmarksEnabled_;
			UIEventStream* eventStream_;
			ChatListModel* model_;
			ChatListDelegate* delegate_;
			QMenu* mucMenu_;
			QMenu* emptyMenu_;
			QMenu* mucRecentsMenu_;
			ChatListItem* contextMenuItem_;
			SettingsProvider* settings_;
			QList<QAction*> onlineOnlyActions_;
			bool isOnline_;
	};

}
