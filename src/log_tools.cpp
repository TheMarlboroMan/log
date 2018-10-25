#include "log_tools.h"

using namespace tools;


log& tools::error(tools::log& _l) {

	_l<<tools::lop::lock<<tools::ltime::datetime<<tools::lin::error;
	return _l;
}

log& tools::warning(tools::log& _l) {

	_l<<tools::lop::lock<<tools::ltime::datetime<<tools::lin::warning;
	return _l;
}

log& tools::info(tools::log& _l) {

	_l<<tools::lop::lock<<tools::ltime::datetime<<tools::lin::info;
	return _l;
}

log& tools::debug(tools::log& _l) {

	_l<<tools::lop::lock<<tools::ltime::datetime<<tools::lin::debug;
	return _l;
}

//TODO: This is funky... Even if the mode is not allowed, we still print...
lop tools::endl(tools::log& _l) {

	if(_l.check_levels()) {
		_l<<"\n";
	}
	return lop::unlock;
}
