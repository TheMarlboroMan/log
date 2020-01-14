#include <lm/tools.h>

using namespace lm;

int lm::lvl_to_int(lvl _lin) {

	switch(_lin) {
		case lvl::emergency: return levels::emergency;
		case lvl::alert:     return levels::alert;
		case lvl::critical:  return levels::critical;
		case lvl::error:     return levels::error;
		case lvl::warning:   return levels::warning;
		case lvl::notice:    return levels::notice;
		case lvl::info:      return levels::info;
		case lvl::debug:     return levels::debug;
	}

	return levels::all;
}

