#include "log_tools.h"

using namespace tools;

log& tools::emergency(tools::log& _l) {

	return quick_log(_l, tools::lin::emergency);
}

log& tools::alert(tools::log& _l) {

	return quick_log(_l, tools::lin::alert);
}

log& tools::critical(tools::log& _l) {

	return quick_log(_l, tools::lin::critical);
}

log& tools::error(tools::log& _l) {

	return quick_log(_l, tools::lin::error);
}

log& tools::warning(tools::log& _l) {

	return quick_log(_l, tools::lin::warning);
}

log& tools::notice(tools::log& _l) {

	return quick_log(_l, tools::lin::notice);
}

log& tools::info(tools::log& _l) {

	return quick_log(_l, tools::lin::info);
}

log& tools::debug(tools::log& _l) {

	return quick_log(_l, tools::lin::debug);
}

log& tools::quick_log(tools::log& _l, tools::lin _lin) {

	_l<<llock{};
	ltagout tstatus=_l.tag_status;
	_l<<ltagout::silent<<_lin;
	if(_l.check_levels()) {
		_l<<tstatus<<tools::ltime::datetime<<_lin;
	}

	return _l<<tstatus;
}

lunlocknl tools::endl() {

	return lunlocknl{};
}
