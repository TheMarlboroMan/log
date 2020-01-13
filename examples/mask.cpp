//This example will use a ostream_logger: a log that writes to an output stream.
#include "../src/ostream_logger.h"

//Of course, we need the sentries to write to a logger.
#include "../src/sentry.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace log;

void say_something(log::logger& _logger);

int main(int, char **) {

	std::cout<<"Building a ostream logger from std::cout..."<<std::endl;
	log::ostream_logger ol(std::cout);

	std::cout<<"Current mask value :"<<ol.get_mask()<<std::endl;

	//Using all levels...
	say_something(ol);

	//Masking some levels...
	std::cout<<"We will mask out error and info now..."<<std::endl;
	int mask_value=log::levels::all;
	mask_value&=~log::levels::error;
	mask_value&=~log::levels::info;
	ol.set_mask(mask_value);
	//TODO: There's a bug here: a couple of spaces are inserted...
	std::cout<<"Current mask value :"<<ol.get_mask()<<std::endl;
	say_something(ol);

	return 0;
}

void say_something(log::logger& _logger) {

	log::log(_logger, log::lvl::emergency)<<"State of emergency!"<<std::endl;
	log::log(_logger, log::lvl::alert)<<"This is an alert"<<std::endl;
	log::log(_logger, log::lvl::critical)<<"This is a critical entry"<<std::endl;
	log::log(_logger, log::lvl::error)<<"This is an error"<<std::endl;
	log::log(_logger, log::lvl::warning)<<"This is merely a warning"<<std::endl;
	log::log(_logger, log::lvl::notice)<<"This is just a notice..."<<std::endl;
	log::log(_logger, log::lvl::info)<<"Some info here..."<<std::endl;
	log::log(_logger, log::lvl::debug)<<"And debug"<<std::endl;
}
