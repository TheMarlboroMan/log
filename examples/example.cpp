#include <iostream>
#include <limits>
#include <string>
#include "../src/sentry.h"
#include "../src/file_logger.h"
#include "../src/void_logger.h"
#include "../src/ostream_logger.h"

//This example shows how to use all three different loggers in a non-threaded
//way.
void show_menu();
int get_option();
void log_data(lm::logger&);

int main(int, char **) {

	//First, let us instance a logger of each kind.
	lm::file_logger fl("example.log");
	lm::void_logger vl;
	lm::ostream_logger ol(std::cout);

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
