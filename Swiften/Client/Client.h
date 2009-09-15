#ifndef SWIFTEN_Client_H
#define SWIFTEN_Client_H

#include <boost/signals.hpp>
#include <boost/shared_ptr.hpp>

#include "Swiften/Client/ClientSession.h"
#include "Swiften/Client/ClientError.h"
#include "Swiften/Elements/Presence.h"
#include "Swiften/Elements/Message.h"
#include "Swiften/JID/JID.h"
#include "Swiften/Base/String.h"
#include "Swiften/Base/IDGenerator.h"
#include "Swiften/Client/StanzaChannel.h"
#include "Swiften/Queries/IQRouter.h"
#include "Swiften/Parser/PayloadParsers/FullPayloadParserFactoryCollection.h"
#include "Swiften/Serializer/PayloadSerializers/FullPayloadSerializerCollection.h"

namespace Swift {
	class TLSLayerFactory;
	class ConnectionFactory;
	class ClientSession;

	class Client : public StanzaChannel, public IQRouter, public boost::bsignals::trackable {
		public:
			Client(const JID& jid, const String& password);
			~Client();

			void setCertificate(const String& certificate);

			void connect();
			void disconnect();
			
			bool isAvailable();

			virtual void sendIQ(boost::shared_ptr<IQ>);
			virtual void sendMessage(boost::shared_ptr<Message>);
			virtual void sendPresence(boost::shared_ptr<Presence>);

		public:
			boost::signal<void (ClientError)> onError;
			boost::signal<void ()> onConnected;
			boost::signal<void (const String&)> onDataRead;
			boost::signal<void (const String&)> onDataWritten;

		private:
			void handleConnectionConnectFinished(bool error);
			void send(boost::shared_ptr<Stanza>);
			virtual String getNewIQID();
			void handleElement(boost::shared_ptr<Element>);
			void handleSessionFinished(const boost::optional<Session::SessionError>& error);
			void handleNeedCredentials();
			void handleDataRead(const ByteArray&);
			void handleDataWritten(const ByteArray&);

		private:
			JID jid_;
			String password_;
			IDGenerator idGenerator_;
			ConnectionFactory* connectionFactory_;
			TLSLayerFactory* tlsLayerFactory_;
			FullPayloadParserFactoryCollection payloadParserFactories_;
			FullPayloadSerializerCollection payloadSerializers_;
			boost::shared_ptr<ClientSession> session_;
			boost::shared_ptr<Connection> connection_;
			String certificate_;
	};
}

#endif
