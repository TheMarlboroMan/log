#ifndef LOG_EXCEPTION_H
#define LOG_EXCEPTION_H

#include <stdexcept>

namespace log {

class exception:
	public std::runtime_error {

	public:

						exception(const std::string& _err)
		:std::runtime_error{_err} {

	}
};

}

#endif
