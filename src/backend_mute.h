#ifndef LOG_BACKEND_MUTE_H
#define LOG_BACKEND_MUTE_H

#include "backend.h"

namespace log {

class backend_mute
	:public backend {

	public:

	void				commit(const std::string&) {}
};

}

#endif

