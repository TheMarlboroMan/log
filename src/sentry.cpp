#include "sentry.h"

using namespace log;

locking_sentry log::lock(logger& _logger, lvl _type) {

	locking_sentry_mutex.lock();
	_logger<<log::now()<<" "<<_type<<" ";
	return locking_sentry{_logger};
}

sentry log::log(logger& _logger, lvl _type) {

	_logger<<log::now()<<" "<<_type<<" ";
	return sentry{_logger};
}


locking_sentry::locking_sentry(logger& _logger)
		:logger_instance(_logger) {

}

locking_sentry::~locking_sentry() {

	locking_sentry_mutex.unlock();
}

sentry::sentry(logger& _logger)
	:logger_instance(_logger) {
	
}
