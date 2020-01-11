#include "file_logger.h"
#include "definitions.h"
#include "tools.h"

using namespace log;

file_logger::file_logger(const char * _filename)
	:filename{_filename}, 
	s{filename} {
	
}
