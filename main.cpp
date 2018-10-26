#include "src/log.h"
#include "src/log_tools.h"

int main(int /*argc*/, char ** /*argv*/) {

	using namespace tools;

	log l("testlog.log");

	l<<lcut(log::info | log::error)
		<<lin::debug<<"THIS DEBUG SHOULD NOT BE PRINTED"<<std::endl
		<<lin::warning<<"THIS WARNING SHOULD NOT BE PRINTED"<<std::endl
		<<lin::info<<"THIS INFO SHOULD BE PRINTED"<<std::endl
		<<lin::error<<"THIS ERROR SHOULD BE PRINTED"<<std::endl;

	l<<lcut(log::all)<<"-------- DONE WITH THE FIRST ROUND OF TESTS"
		<<lcut(log::info | log::error);

	debug(l)<<"THIS LOCKED DEBUG SHOULD NOT BE PRINTED"<<endl(l);
	info(l)<<"THIS LOCKED INFO SHOULD BE PRINTED"<<endl(l);
	error(l)<<"THIS LOCKED ERROR SHOULD BE PRINTED"<<endl(l);
	warning(l)<<"THIS LOCKED WARNING SHOULD NOT BE PRINTED"<<endl(l);


	return 1;

}
