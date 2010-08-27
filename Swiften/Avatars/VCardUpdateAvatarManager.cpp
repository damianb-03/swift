/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include "Swiften/Avatars/VCardUpdateAvatarManager.h"

#include <boost/bind.hpp>

#include "Swiften/Client/StanzaChannel.h"
#include "Swiften/Elements/VCardUpdate.h"
#include "Swiften/Queries/Requests/GetVCardRequest.h"
#include "Swiften/StringCodecs/SHA1.h"
#include "Swiften/StringCodecs/Hexify.h"
#include "Swiften/Avatars/AvatarStorage.h"
#include "Swiften/MUC/MUCRegistry.h"
#include "Swiften/VCards/VCardManager.h"

namespace Swift {

VCardUpdateAvatarManager::VCardUpdateAvatarManager(VCardManager* vcardManager, StanzaChannel* stanzaChannel, AvatarStorage* avatarStorage, MUCRegistry* mucRegistry) : vcardManager_(vcardManager), stanzaChannel_(stanzaChannel), avatarStorage_(avatarStorage), mucRegistry_(mucRegistry) {
	stanzaChannel->onPresenceReceived.connect(boost::bind(&VCardUpdateAvatarManager::handlePresenceReceived, this, _1));
	vcardManager_->onVCardChanged.connect(boost::bind(&VCardUpdateAvatarManager::handleVCardChanged, this, _1, _2));
}

VCardUpdateAvatarManager::~VCardUpdateAvatarManager() {

}

void VCardUpdateAvatarManager::setMUCRegistry(MUCRegistry* mucRegistry) {
	mucRegistry_ = mucRegistry;
}

void VCardUpdateAvatarManager::handlePresenceReceived(boost::shared_ptr<Presence> presence) {
	boost::shared_ptr<VCardUpdate> update = presence->getPayload<VCardUpdate>();
	if (!update || presence->getPayload<ErrorPayload>()) {
		return;
	}
	JID from = getAvatarJID(presence->getFrom());
	if (getAvatarHash(from) == update->getPhotoHash()) {
		return;
	}
	if (avatarStorage_->hasAvatar(update->getPhotoHash())) {
		setAvatarHash(from, update->getPhotoHash());
	}
	else {
		vcardManager_->requestVCard(from);
	}
}

void VCardUpdateAvatarManager::handleVCardChanged(const JID& from, VCard::ref vCard) {
	if (!vCard) {
		std::cerr << "Warning: " << from << ": null vcard payload" << std::endl;
		return;
	}

	String hash = Hexify::hexify(SHA1::getHash(vCard->getPhoto()));
	avatarStorage_->addAvatar(hash, vCard->getPhoto());
	setAvatarHash(from, hash);
}

void VCardUpdateAvatarManager::setAvatarHash(const JID& from, const String& hash) {
	avatarHashes_[from] = hash;
	onAvatarChanged(from, hash);
}

/*
void VCardUpdateAvatarManager::setAvatar(const JID& jid, const ByteArray& avatar) {
	String hash = Hexify::hexify(SHA1::getHash(avatar));
	avatarStorage_->addAvatar(hash, avatar);
	setAvatarHash(getAvatarJID(jid), hash);
}
*/

String VCardUpdateAvatarManager::getAvatarHash(const JID& jid) const {
	std::map<JID, String>::const_iterator i = avatarHashes_.find(getAvatarJID(jid));
	if (i != avatarHashes_.end()) {
		return i->second;
	}
	else {
		return "";
	}
}

boost::filesystem::path VCardUpdateAvatarManager::getAvatarPath(const JID& jid) const {
	String hash = getAvatarHash(jid);
	if (!hash.isEmpty()) {
		return avatarStorage_->getAvatarPath(hash);
	}
	return boost::filesystem::path();
}

JID VCardUpdateAvatarManager::getAvatarJID(const JID& jid) const {
	JID bareFrom = jid.toBare();
	return (mucRegistry_ && mucRegistry_->isMUC(bareFrom)) ? jid : bareFrom;
}


}