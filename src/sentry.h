#ifndef LOG_SENTRY_H
#define LOG_SENTRY_H

#include <sstream>

#include "definitions.h"

namespace log {

class base_log;

//!Class returned from any log once logging starts... All it does is accumulate
//!logging information. Once this instance is destroyed, all accumulated data
//!is commited to the log class.
class sentry {

	public:

	//!Class constructor. Client code is NOT supposed to create these.
								sentry(base_log&, lin);

	//!We are not supposed to copy sentries around... In fact, this will make
	//!the program stop, but we seem to need it to be able to return sentries
	//!from the log_base class.
								sentry(const sentry&);
								~sentry();

	template<class T> 
	sentry&		 				operator<<(const T& _value) {

		//TODO: Could save some conversions here if we were aware of mute loggers.
		buffer<<_value;
		return *this;
	}

	//!Accepts std::ostream modifiers.
	sentry& operator<<(std::ostream& ( *pf )(std::ostream&));

	//!Accepts std::ios modifiers.
	sentry& operator<<(std::ios& ( *pf )(std::ios&));

	//!Accepts std::ios_base modifiers.
	sentry& operator<<(std::ios_base& ( *pf )(std::ios_base&));

	private:

	base_log&					log;
	//TODO: It would be nice if we had a stream hierarchy thing, for the mute
	//loggers.
	std::stringstream			buffer;
};

}

#endif
