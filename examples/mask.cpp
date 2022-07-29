//This example will use a ostream_logger: a log that writes to an output stream.
#include <lm/ostream_logger.h>

//Of course, we need the sentries to write to a logger.
#include <lm/log.h>

#include <iostream>
#include <vector>
#include <cmath>

using namespace lm;

void say_something(lm::logger& _logger);

int main(int, char **) {

	std::cout<<"Building a ostream logger from std::cout..."<<std::endl;
	lm::ostream_logger ol(std::cout);

	std::cout<<"Current mask value :"<<ol.get_mask()<<std::endl;

	//Using all levels...
	say_something(ol);

	//Masking some levels...
	std::cout<<"We will mask out error and info now..."<<std::endl;
	int mask_value=lm::levels::all;
	mask_value&=~lm::levels::error;
	mask_value&=~lm::levels::info;
	ol.set_mask(mask_value);
	//TODO: There's a bug here: a couple of spaces are inserted...
	std::cout<<"Current mask value :"<<ol.get_mask()<<std::endl;
	say_something(ol);

	return 0;
}

void say_something(lm::logger& _logger) {

	lm::log(_logger).emergency()<<"State of emergency!"<<std::endl;
	lm::log(_logger).alert()<<"This is an alert"<<std::endl;
	lm::log(_logger).critical()<<"This is a critical entry"<<std::endl;
	lm::log(_logger).error()<<"This is an error"<<std::endl;
	lm::log(_logger).warning()<<"This is merely a warning"<<std::endl;
	lm::log(_logger).notice()<<"This is just a notice..."<<std::endl;
	lm::log(_logger).info()<<"Some info here..."<<std::endl;
	lm::log(_logger).debug()<<"And debug"<<std::endl;
}
