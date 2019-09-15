#ifndef LOG_BACKEND_H
#define LOG_BACKEND_H

#include <string>

namespace log {

//!A stream is whatever is at the end of the log to store the log lines. This
//is the base class for them all.
class backend {
	public:

	virtual void				commit(const std::string& _str)=0;
	virtual						~backend() {}
};

}

#endif
