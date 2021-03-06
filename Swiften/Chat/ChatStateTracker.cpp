/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Chat/ChatStateTracker.h>

namespace Swift {
ChatStateTracker::ChatStateTracker() {
	currentState_ = ChatState::Gone;
}

void ChatStateTracker::handleMessageReceived(boost::shared_ptr<Message> message) {
	if (message->getType() == Message::Error) {
		return;
	}
	boost::shared_ptr<ChatState> statePayload = message->getPayload<ChatState>();
	if (statePayload) {
		changeState(statePayload->getChatState());;
	}
}

void ChatStateTracker::handlePresenceChange(boost::shared_ptr<Presence> newPresence) {
	if (newPresence->getType() == Presence::Unavailable) {
		onChatStateChange(ChatState::Gone);
	}
}

void ChatStateTracker::changeState(ChatState::ChatStateType state) {
	if (state != currentState_) {
		currentState_ = state;
		onChatStateChange(state);
	}
}

}
