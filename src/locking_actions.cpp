#include "locking_actions.h"

#include <utility>

using namespace log;

locking_action log::lock(logger& _logger) {

	locking_actions_mutex.lock();
	return locking_action{_logger};	
}

locking_action::locking_action(logger& _logger)
		:logger_instance{_logger} {
		
}

locking_action::~locking_action() {

	locking_actions_mutex.unlock();
}

/*
logger& log::emergency(logger& _l) {

	return quick_log(_l, lin::emergency);
}

logger& log::alert(logger& _l) {

	return quick_log(_l, lin::alert);
}

logger& log::critical(logger& _l) {

	return quick_log(_l, lin::critical);
}

logger& log::error(logger& _l) {

	return quick_log(_l, lin::error);
}

logger& log::warning(logger& _l) {

	return quick_log(_l, lin::warning);
}

logger& log::notice(logger& _l) {

	return quick_log(_l, lin::notice);
}

logger& log::info(logger& _l) {

	return quick_log(_l, lin::info);
}

logger& log::debug(logger& _l) {

	return quick_log(_l, lin::debug);
}

logger& log::quick_log(logger& _l, lin _lin) {

	_l<<llock{};
	ltagout tstatus=_l.tag_status;
	_l<<ltagout::silent<<_lin;
//TODO: We'll see... 
//	if(_l.check_levels()) {
		_l<<tstatus<<ltime::datetime<<_lin;
//	}

	return _l<<tstatus;
}

lunlocknl log::endl() {

	return lunlocknl{};
}
*/
