#include "tools.h"

using namespace log;

int log::lin_to_int(lin _lin) {

	switch(_lin) {
		case lin::emergency: return levels::emergency;
		case lin::alert:     return levels::alert;
		case lin::critical:  return levels::critical;
		case lin::error:     return levels::error;
		case lin::warning:   return levels::warning;
		case lin::notice:    return levels::notice;
		case lin::info:      return levels::info;
		case lin::debug:     return levels::debug;
	}

	return levels::all;
}

