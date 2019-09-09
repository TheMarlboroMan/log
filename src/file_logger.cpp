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

logger& file_logger::operator<<(lin _lvl) {

	std::string tag=lin_to_tag(_lvl);
	entry_level=lin_to_int(_lvl);

	//TODO: This makes no sense anymore, all tagout stuff can be removed...
	if(tag_status==ltagout::verbose && check_levels(lin_to_int(_lvl))) {
		s<<tag;
	}

	return *this;
}

//TODO: Can be removed.
logger& file_logger::operator<<(ltagout _lt) {

	tag_status=_lt;
	return *this;
}

logger& file_logger::operator<<(lcut _lcut) {

	allowed_levels=_lcut.value;
	return *this;
}

logger& file_logger::operator<<(ltime v) {
	
	switch(v) {
		case ltime::time:
			s<<("[")<<time()<<"] ";
		break;
		case ltime::date:
			s<<("[")<<date()<<"] ";
		break;
		case ltime::datetime:
			s<<("[")<<date()<<" "<<time()<<"] ";
		break;
	}

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
