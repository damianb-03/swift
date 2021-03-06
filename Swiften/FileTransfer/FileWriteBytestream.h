/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/FileTransfer/WriteBytestream.h>

namespace Swift {
	class SWIFTEN_API FileWriteBytestream : public WriteBytestream {
		public:
			FileWriteBytestream(const boost::filesystem::path& file);
			~FileWriteBytestream();

			virtual void write(const std::vector<unsigned char>&);
			void close();

		private:
			boost::filesystem::path file;
			boost::filesystem::ofstream* stream;
	};
}
