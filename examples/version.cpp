#include <iostream>
#include <lm/log.h>
#include <lm/lib.h>

int main(int, char **) {

	std::cout<<"log version "<<lm::get_lib_version()<<std::endl;
	return 1;
}
