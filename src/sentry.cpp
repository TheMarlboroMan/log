#include "sentry.h"

#include <cassert>
#include "tools.h"
#include "base_log.h"

using namespace log;

sentry::sentry(base_log& _log, lin _input_level):
	log{_log} {

	(*this)<<date()<<" "<<time()<<" "<<lin_to_tag(_input_level)<<" ";
}

sentry::sentry(const sentry& _other):
	log{_other.log} {

	//!Intentionally make the program explode. We are not supposed to copy these
	//!around
	assert(false);
}

sentry::~sentry() {

	log.commit(buffer.str());
}

sentry& sentry::operator<<(std::ostream& ( *pf )(std::ostream&)) {

	buffer<<pf;
	return *this;
}

sentry& sentry::operator<<(std::ios& ( *pf )(std::ios&)) {

	buffer<<pf;
	return *this;
}

sentry& sentry::operator<<(std::ios_base& ( *pf )(std::ios_base&)) {

	buffer<<pf;
	return *this;
}
