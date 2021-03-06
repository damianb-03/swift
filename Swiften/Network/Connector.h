/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <deque>
#include <Swiften/Base/boost_bsignals.h>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <Swiften/Base/API.h>
#include <Swiften/Network/DomainNameServiceQuery.h>
#include <Swiften/Network/Connection.h>
#include <Swiften/Network/Timer.h>
#include <Swiften/Network/HostAddressPort.h>
#include <string>
#include <Swiften/Network/DomainNameResolveError.h>

namespace Swift {
	class DomainNameAddressQuery;
	class DomainNameResolver;
	class ConnectionFactory;
	class TimerFactory;

	class SWIFTEN_API Connector : public boost::bsignals::trackable, public boost::enable_shared_from_this<Connector> {
		public:
			typedef boost::shared_ptr<Connector> ref;

			static Connector::ref create(const std::string& hostname, int port, const boost::optional<std::string>& serviceLookupPrefix, DomainNameResolver* resolver, ConnectionFactory* connectionFactory, TimerFactory* timerFactory) {
				return ref(new Connector(hostname, port, serviceLookupPrefix, resolver, connectionFactory, timerFactory));
			}

			void setTimeoutMilliseconds(int milliseconds);
			/**
			 * Start the connection attempt.
			 * Note that after calling this method, the caller is responsible for calling #stop()
			 * if it wants to cancel it. Not doing so can leak references.
			 */
			void start();
			void stop();

			boost::signal<void (boost::shared_ptr<Connection>, boost::shared_ptr<Error>)> onConnectFinished;

		private:
			Connector(const std::string& hostname, int port, const boost::optional<std::string>& serviceLookupPrefix, DomainNameResolver*, ConnectionFactory*, TimerFactory*);

			void handleServiceQueryResult(const std::vector<DomainNameServiceQuery::Result>& result);
			void handleAddressQueryResult(const std::vector<HostAddress>& address, boost::optional<DomainNameResolveError> error);
			void queryAddress(const std::string& hostname);

			void tryNextServiceOrFallback();
			void tryNextAddress();
			void tryConnect(const HostAddressPort& target);

			void handleConnectionConnectFinished(bool error);
			void finish(boost::shared_ptr<Connection>);
			void handleTimeout();


		private:
			std::string hostname;
			int port;
			boost::optional<std::string> serviceLookupPrefix;
			DomainNameResolver* resolver;
			ConnectionFactory* connectionFactory;
			TimerFactory* timerFactory;
			int timeoutMilliseconds;
			boost::shared_ptr<Timer> timer;
			boost::shared_ptr<DomainNameServiceQuery> serviceQuery;
			std::deque<DomainNameServiceQuery::Result> serviceQueryResults;
			boost::shared_ptr<DomainNameAddressQuery> addressQuery;
			std::deque<HostAddress> addressQueryResults;
			bool queriedAllServices;
			boost::shared_ptr<Connection> currentConnection;
			bool foundSomeDNS;
	};
}
