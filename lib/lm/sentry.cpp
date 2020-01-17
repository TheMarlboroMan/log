#include <lm/sentry.h>

using namespace lm;

std::mutex locking_sentry::locking_sentry_mutex;

locking_sentry lm::lock(logger& _logger, lvl _type) {

	locking_sentry::locking_sentry_mutex.lock();
	_logger<<lm::now()<<" "<<_type<<" ";
	return locking_sentry{_logger};
}

sentry lm::log(logger& _logger, lvl _type) {

	_logger<<lm::now()<<" "<<_type<<" ";
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
