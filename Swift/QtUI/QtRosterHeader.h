/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QToolButton>

#include <string>
#include <Swiften/Elements/StatusShow.h>
#include <Swiften/Elements/VCard.h>
#include <Swift/Controllers/Roster/ContactRosterItem.h>

#include "QtTextEdit.h"

class QHBoxLayout;

namespace Swift {
	class QtClickableLabel;
	class QtStatusWidget;
	class QtNameWidget;
	class SettingsProvider;
	class StatusCache;
	
	class QtRosterHeader : public QWidget {
		Q_OBJECT
	public:
		QtRosterHeader(SettingsProvider* settings, StatusCache* statusCache, QWidget* parent = NULL);
		void setAvatar(const QString& path);

		void setJID(const QString& jid);
		void setNick(const QString& nick);
		void setContactRosterItem(boost::shared_ptr<ContactRosterItem> contact);

		void setStatusText(const QString& statusMessage);
		void setStatusType(StatusShow::Type type);
		void setConnecting();
		void setStreamEncryptionStatus(bool tlsInPlace);
	private:
		bool event(QEvent* event);
	signals:
		void onChangeStatusRequest(StatusShow::Type showType, const QString &statusMessage);
		void onEditProfileRequest();
		void onShowCertificateInfo();

	private slots:
		void handleChangeStatusRequest(StatusShow::Type type, const QString &statusMessage);
	private:
		QString name_;
		QtClickableLabel* avatarLabel_;
		QtNameWidget* nameWidget_;
		QtTextEdit* statusEdit_;
		QtStatusWidget* statusWidget_;
		QToolButton* securityInfoButton_;
		static const int avatarSize_;
		boost::shared_ptr<ContactRosterItem> contact_;
	};
}
