#include "file_logger.h"
#include "definitions.h"
#include "tools.h"

using namespace log;

file_logger::file_logger(const char * _filename)
	:filename{_filename}, 
	s{filename} {
	
}

file_logger::~file_logger() {

	s.close();
}

//TODO:was it not for the check_levels, this could be defined in the parent class.
//The whole check_levels thing is shady anyway... 

//TODO: FUck this, really...

logger& file_logger::operator<<(lin _lvl) {

	std::string tag=lin_to_tag(_lvl);
	entry_level=lin_to_int(_lvl);

	if(check_levels(lin_to_int(_lvl))) {
		s<<tag;
	}

	return *this;
}

logger& file_logger::operator<<(lcut _lcut) {

	allowed_levels=_lcut.value;
	return *this;
}

logger& file_logger::operator<<(std::ostream& ( *pf )(std::ostream&)) {

	if(check_levels()) {
		s<<pf;
	}
	return *this;
}

logger& file_logger::operator<<(std::ios& ( *pf )(std::ios&)) {

	if(check_levels()) {
		s<<pf;
	}
	return *this;
}

logger& file_logger::operator<<(std::ios_base& ( *pf )(std::ios_base&)) {

	if(check_levels()) {
		s<<pf;
	}
	return *this;
}
