#ifndef LOG_BACKEND_STREAM_H
#define LOG_BACKEND_STREAM_H

#include <iostream>

#include "backend.h"

namespace log {

//!A stream that works with an underlying C++ stream, such as cerr, cout, 
//!a file stream...
class backend_stream:
	public backend {

	public:

								backend_stream(std::ostream&);
	virtual void				commit(const std::string&);

	private:

	std::ostream&				streamref;
};

}

#endif
