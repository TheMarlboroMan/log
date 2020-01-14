#include <lm/file_logger.h>

#include <stdexcept>

using namespace lm;

file_logger::file_logger(const char * _filename)
	:filename{_filename}, 
	s{filename} {
	
	if(!s) {
		//TODO THe library should throw its own exceptions
		throw std::runtime_error(
			std::string("could not open log file ")
			+_filename
		);
	}
}
