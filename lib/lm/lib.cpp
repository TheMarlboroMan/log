#include <lm/lib.h>
#include <sstream>
using namespace lm;

std::string lm::get_lib_version() {

	std::stringstream ss;
	ss<<MAJOR_VERSION<<"."<<MINOR_VERSION<<"."<<PATCH_VERSION<<BUILD_VERSION;
	return ss.str();
} 
