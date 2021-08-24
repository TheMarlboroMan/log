#include <lm/sentry.h>

using namespace lm;

std::mutex locking_sentry::locking_sentry_mutex;

locking_sentry lm::lock(logger& _logger, lvl _type) {

	locking_sentry::locking_sentry_mutex.lock();
	_logger<<lm::now<<" "<<_type<<" ";
	return locking_sentry{_logger};
}

locking_sentry lm::lock(logger& _logger, manip_debug) {return lock(_logger, lvl::debug);}
locking_sentry lm::lock(logger& _logger, manip_info) {return lock(_logger, lvl::info);}
locking_sentry lm::lock(logger& _logger, manip_notice) {return lock(_logger, lvl::notice);}
locking_sentry lm::lock(logger& _logger, manip_warning) {return lock(_logger, lvl::warning);}
locking_sentry lm::lock(logger& _logger, manip_error) {return lock(_logger, lvl::error);}
locking_sentry lm::lock(logger& _logger, manip_critical) {return lock(_logger, lvl::critical);}
locking_sentry lm::lock(logger& _logger, manip_alert) {return lock(_logger, lvl::alert);}
locking_sentry lm::lock(logger& _logger, manip_emergency) {return lock(_logger, lvl::emergency);}

sentry lm::log(logger& _logger, lvl _type) {

	_logger<<lm::now<<" "<<_type<<" ";
	return sentry{_logger};
}

sentry lm::log(logger& _logger, manip_debug) {return log(_logger, lvl::debug);}
sentry lm::log(logger& _logger, manip_info) {return log(_logger, lvl::info);}
sentry lm::log(logger& _logger, manip_notice) {return log(_logger, lvl::notice);}
sentry lm::log(logger& _logger, manip_warning) {return log(_logger, lvl::warning);}
sentry lm::log(logger& _logger, manip_error) {return log(_logger, lvl::error);}
sentry lm::log(logger& _logger, manip_critical) {return log(_logger, lvl::critical);}
sentry lm::log(logger& _logger, manip_alert) {return log(_logger, lvl::alert);}
sentry lm::log(logger& _logger, manip_emergency) {return log(_logger, lvl::emergency);}

locking_sentry::locking_sentry(logger& _logger)
		:logger_instance(_logger) {

}

locking_sentry::~locking_sentry() {

	locking_sentry_mutex.unlock();
}

sentry::sentry(logger& _logger)
	:logger_instance(_logger) {
	
}
