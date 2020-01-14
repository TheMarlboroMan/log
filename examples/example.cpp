#include <lm/sentry.h>
#include <lm/file_logger.h>
#include <lm/void_logger.h>
#include <lm/ostream_logger.h>

#include <iostream>
#include <limits>
#include <string>

//This example shows how to use all three different loggers in a non-threaded
//way.
void show_menu();
int get_option();
void log_data(lm::logger&);
void test_types(lm::logger&);

int main(int, char **) {

	//First, let us instance a logger of each kind.
	lm::file_logger fl("example.log");
	lm::void_logger vl;
	lm::ostream_logger ol(std::cout);

	test_types(ol);
	//Now ask the user for a log to use and a message...
	while(true){
		show_menu();
		int option=get_option();
		switch(option) {
			case 0:
				return 0;
			case 1: log_data(fl); break;
			case 2: log_data(ol); break;
			case 3:	log_data(vl); break;
				
			default:
				std::cout<<"Invalid option"<<std::endl;
			break;
		}		
	}
}

void show_menu() {

	std::cout<<"0: Exit\n1: Use file log (example.log)\n2: Use ostream log\n3: Use void logger (no output)\n\n>>";
	std::flush(std::cout);
}

int get_option() {
	int result=0;
	std::cin>>result;
	if(std::cin.fail()) {
		result=99;
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return result;
}

void log_data(lm::logger& _logger) {

	std::cout<<"Enter message: >>";
	std::string msg;
	std::getline(std::cin, msg);
	lm::log(_logger, lm::lvl::info)<<msg<<std::endl;
}

void test_types(lm::logger& _logger) {

	int intval=-1;
	unsigned int unsignedintval=1;
	long longval=-1;
	unsigned long unsignedlongval=1;
	double doubleval=3.3;
	float floatval=3.5f;
	const char * cstrval="Hello";
	char charval='a';
	std::string strval{"There"};

	lm::log(_logger, lm::lvl::info)<<"Testing output of types..."<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"int: "<<intval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"unsigned int: "<<unsignedintval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"long: "<<longval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"unsigned long: "<<unsignedlongval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"double: "<<doubleval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"float: "<<floatval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"const char *: "<<cstrval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"char: "<<charval<<std::endl;
	lm::log(_logger, lm::lvl::info)<<"std::string: "<<strval<<std::endl;

}
