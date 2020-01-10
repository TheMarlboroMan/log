#include "locking_actions.h"

#include <utility>
#include "tools.h"

using namespace log;

locking_action log::lock(logger& _logger, lin _type) {

	locking_actions_mutex.lock();
	//Add the time and tag...
	switch(_type) {
		case lin::emergency: _logger.emergency(); break;
		case lin::alert:     _logger.alert(); break;
		case lin::critical:  _logger.critical(); break;
		case lin::error:     _logger.error(); break;
		case lin::warning:   _logger.warning(); break;
		case lin::notice:    _logger.notice(); break;
		case lin::info:      _logger.info(); break;
		case lin::debug:     _logger.debug(); break;
	}

	return locking_action{_logger};
}

locking_action::locking_action(logger& _logger)
		:logger_instance(_logger) {

}

locking_action::~locking_action() {

	locking_actions_mutex.unlock();
}
