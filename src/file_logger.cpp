#include "file_logger.h"

#include "exception.h"

using namespace log;

file_logger::file_logger(const std::string& _filename)
	:file{_filename.c_str()}, internal_stream(file) {

	if(!file) {
		throw exception(
			std::string("could not open log file ")
			+_filename
		);
	}
}
