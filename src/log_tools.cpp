#include "log_tools.h"

using namespace tools;


log& tools::error(tools::log& _l) {

	return quick_log(_l, tools::lin::error);
}

log& tools::warning(tools::log& _l) {

	return quick_log(_l, tools::lin::warning);
}

log& tools::info(tools::log& _l) {

	return quick_log(_l, tools::lin::info);
}

log& tools::debug(tools::log& _l) {

	return quick_log(_l, tools::lin::debug);
}

log& tools::quick_log(tools::log& _l, tools::lin _lin) {

	ltagout tstatus=_l.tag_status;
	_l<<ltagout::silent<<_lin;
	if(_l.check_levels()) {
		_l<<tools::lop::lock<<tstatus<<tools::ltime::datetime<<_lin;
	}

	return _l<<tstatus;
}

//TODO: This is funky... Even if the mode is not allowed, we still print...
lop tools::endl(tools::log& _l) {

	if(_l.check_levels()) {
		_l<<"\n";
	}
	return lop::unlock;
}
