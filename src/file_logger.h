#ifndef LOG_FILE_LOGGER_H
#define LOG_FILE_LOGGER_H

#include <fstream>

#include "base_log.h"
#include "backend_stream.h"

namespace log {

class file_logger:
	public base_log {

	public:
							file_logger(const std::string&);

	protected:

	backend&				get_backend() {return internal_stream;}

	private:

	std::ofstream			file;
	backend_stream			internal_stream;
};

}

#endif
