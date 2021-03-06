/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <vector>
#include <map>

#include <Swiften/Base/API.h>
#include <Swiften/Network/HostAddress.h>
#include <Swiften/Network/HostAddressPort.h>
#include <Swiften/Network/DomainNameResolver.h>
#include <Swiften/Network/DomainNameServiceQuery.h>
#include <Swiften/Network/DomainNameAddressQuery.h>
#include <Swiften/EventLoop/EventLoop.h>

namespace Swift {
	class SWIFTEN_API StaticDomainNameResolver : public DomainNameResolver {
		public:
			typedef std::map<std::string, std::vector<HostAddress> > AddressesMap;
			typedef std::vector< std::pair<std::string, DomainNameServiceQuery::Result> > ServicesCollection;

		public:
			StaticDomainNameResolver(EventLoop* eventLoop);
			~StaticDomainNameResolver();

			void addAddress(const std::string& domain, const HostAddress& address);
			void addService(const std::string& service, const DomainNameServiceQuery::Result& result);
			void addXMPPClientService(const std::string& domain, const HostAddressPort&);
			void addXMPPClientService(const std::string& domain, const std::string& host, int port);

			const AddressesMap& getAddresses() const {
				return addresses;
			}

			const ServicesCollection& getServices() const {
				return services;
			}

			bool getIsResponsive() const {
				return isResponsive;
			}

			void setIsResponsive(bool b) {
				isResponsive = b;
			}

			virtual boost::shared_ptr<DomainNameServiceQuery> createServiceQuery(const std::string& serviceLookupPrefix, const std::string& domain);
			virtual boost::shared_ptr<DomainNameAddressQuery> createAddressQuery(const std::string& name);
		private:
			EventLoop* eventLoop;
			bool isResponsive;
			AddressesMap addresses;
			ServicesCollection services;
			boost::shared_ptr<EventOwner> owner;
	};
}
