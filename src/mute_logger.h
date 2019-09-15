#ifndef LOG_MUTE_LOGGER_H
#define LOG_MUTE_LOGGER_H

#include "base_log.h"
#include "backend_mute.h"

namespace log {

class mute_logger
	:public base_log {

	protected:

	virtual backend&			get_backend() {return mute;}

	private:

	backend_mute				mute;


};

}

#endif
