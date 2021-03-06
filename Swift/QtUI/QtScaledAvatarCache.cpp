/*
 * Copyright (c) 2011 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include "QtScaledAvatarCache.h"

#include <QFileInfo>
#include <QDir>
#include <QPixmap>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QByteArray>

#include <Swiften/Base/Log.h>
#include <Swift/QtUI/QtSwiftUtil.h>

namespace Swift {

QtScaledAvatarCache::QtScaledAvatarCache(int size) : size(size) {
}

QString QtScaledAvatarCache::getScaledAvatarPath(const QString& path) {
	QFileInfo avatarFile(path);
	if (avatarFile.exists()) {
		if (!avatarFile.dir().exists(QString::number(size))) {
			if (!avatarFile.dir().mkdir(QString::number(size))) {
				return path;
			}
		}
		QDir targetDir(avatarFile.dir().absoluteFilePath(QString::number(size)));
		QString targetFile = targetDir.absoluteFilePath(avatarFile.baseName());
		if (!QFileInfo(targetFile).exists()) {
			QPixmap avatarPixmap;
			if (avatarPixmap.load(path)) {
				QPixmap maskedAvatar(avatarPixmap.size());
				maskedAvatar.fill(QColor(0, 0, 0, 0));
				QPainter maskPainter(&maskedAvatar);
				maskPainter.setBrush(Qt::black);
				maskPainter.drawRoundedRect(maskedAvatar.rect(), 25.0, 25.0, Qt::RelativeSize);
				maskPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
				maskPainter.drawPixmap(0, 0, avatarPixmap);
				maskPainter.end();

				if (!maskedAvatar.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation).save(targetFile, "PNG")) {
					return path;
				}
			} else {
				SWIFT_LOG(debug) << "Failed to load " << Q2PSTRING(path) << std::endl;
			}
		}
		return targetFile;
	}
	else {
		return path;
	}
}


}
