/*
 * Copyright (c) 2013 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Queries/GenericRequest.h>
#include <Swift/Controllers/UIEvents/UIEventStream.h>
#include <Swift/Controllers/UIInterfaces/BlockListEditorWidgetFactory.h>

namespace Swift {

class BlockPayload;
class UnblockPayload;
class ClientBlockListManager;
class EventController;

class BlockListController {
public:
	BlockListController(ClientBlockListManager* blockListManager, UIEventStream* uiEventStream, BlockListEditorWidgetFactory* blockListEditorWidgetFactory, EventController* eventController);
	~BlockListController();

private:
	void blockListDifferences(const std::vector<JID> &newBlockList, std::vector<JID>& jidsToUnblock, std::vector<JID>& jidsToBlock) const;

	void handleUIEvent(boost::shared_ptr<UIEvent> event);

	void handleBlockResponse(GenericRequest<BlockPayload>::ref, boost::shared_ptr<BlockPayload>, ErrorPayload::ref error, const std::vector<JID>& jids, bool originEditor);
	void handleUnblockResponse(GenericRequest<UnblockPayload>::ref, boost::shared_ptr<UnblockPayload>, ErrorPayload::ref error, const std::vector<JID>& jids, bool originEditor);

	void handleSetNewBlockList(const std::vector<JID>& newBlockList);

	void handleBlockListChanged();

private:
	ClientBlockListManager* blockListManager_;
	BlockListEditorWidgetFactory* blockListEditorWidgetFactory_;
	BlockListEditorWidget* blockListEditorWidget_;
	EventController* eventController_;
	std::vector<JID> blockListBeforeEdit;
	int remainingRequests_;
	UIEventStream* uiEventStream_;
};

}
