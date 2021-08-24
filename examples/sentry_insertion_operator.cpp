/**
Overloading the << operator a la std::ostream for sentries.
*/
#include <lm/ostream_logger.h> 
#include <lm/sentry.h>
#include <lm/file_logger.h>
#include <lm/void_logger.h>
#include <lm/ostream_logger.h>

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

//This is the main problem with sentries: the operator must be defined twice,
//one to allow for lm::log(logger, lvl)<<stuff and other for a named sentry.
	friend			lm::log_sentry& operator<<(lm::log_sentry&&, const some_class&);
//	friend			lm::sentry& operator<<(lm::sentry&, const some_class&);
};

lm::log_sentry& operator<<(
	lm::log_sentry&&  _sentry,
	const some_class& _instance
) {

	_sentry<<_instance.message<<" - "<<_instance.number;
	return _sentry;
}

/*
lm::sentry& operator<<(
	lm::sentry&  _sentry,
	const some_class& _instance
) {

	_sentry<<_instance.message<<" - "<<_instance.number;
	return _sentry;
}
*/

int main(int, char **) {

	//First, let us instance a logger of each kind.
	lm::file_logger fl("example.log");
	lm::void_logger vl;
	lm::ostream_logger ol(std::cout);

	auto primitives=[](lm::logger& _logger) {

		lm::log(_logger, lm::info)<<"some primitives here "<<33<<std::endl;
	};

	auto insertion=[](lm::logger& _logger) {

		some_class instance{"hello there", 12};
		lm::log(_logger, lm::info)<<instance<<std::endl;
	};

	primitives(fl); primitives(vl); primitives(ol);
	insertion(fl); insertion(vl); insertion(ol);

	return 0;
}

