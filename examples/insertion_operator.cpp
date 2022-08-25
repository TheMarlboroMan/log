/**
Overloading the << operator a la std::ostream for loggers.
*/
#include <lm/ostream_logger.h>
#include <lm/log.h>
#include <lm/file_logger.h>
#include <lm/void_logger.h>
#include <lm/ostream_logger.h>
#include <lm/lib.h>

#include <ostream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace lm;

class some_class {

	public:

					some_class(const std::string _s, int _n):message{_s}, number{_n} {

	}

	std::string		message;
	int				number;

	friend			lm::logger& operator<<(lm::logger&, const some_class&);
};

lm::log& operator<<(
	lm::log&  _logger,
	const some_class& _instance
) {

	return _logger<<_instance.message<<" - "<<_instance.number;
}

int main(int, char **) {

	std::cout<<"lm version: "<<lm::get_lib_version()<<std::endl;

	//First, let us instance a logger of each kind.
	lm::file_logger fl("example.log");
	lm::void_logger vl;
	lm::ostream_logger ol(std::cout);

	auto primitives=[](lm::logger& _logger) {

		lm::log(_logger).info()<<"some primitives here "<<33<<std::endl;
	};

	auto insertion=[](lm::logger& _logger) {

		some_class instance{"hello there", 12};
		lm::log(_logger).info()<<instance<<std::endl;
	};

	primitives(fl); primitives(vl); primitives(ol);
	insertion(fl); insertion(vl); insertion(ol);

	return 0;
}

