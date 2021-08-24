#pragma once

#include "logger.h"

namespace lm {

//!A logger that does nothing and whose purpose is to exist in production 
//!applications without removing log code, as questionable as that might be.
class void_logger
	:public logger {

	//This class has no members, no constructor is neccesary. The parent
	//constructor will be automatically called.

#ifndef OPEN_LOG_OPERATORS
	protected:
#endif

	//!The implementation of logger is just a series of nothings
	virtual logger& operator<<(const char *) {return *this;}
	virtual logger& operator<<(char) {return *this;}
	virtual logger& operator<<(int) {return *this;}
	virtual logger& operator<<(unsigned int) {return *this;}
	virtual logger& operator<<(long int) {return *this;}
	virtual logger& operator<<(unsigned long int) {return *this;}
	virtual logger& operator<<(long long int) {return *this;}
	virtual logger& operator<<(unsigned long long int) {return *this;}
	virtual logger& operator<<(double) {return *this;}
	virtual logger& operator<<(const std::string&) {return *this;}
	virtual logger& operator<<(std::ostream& (*)(std::ostream&)) {return *this;}
	virtual logger& operator<<(std::ios& (*)(std::ios&)) {return *this;}
	virtual logger& operator<<(std::ios_base& (*)(std::ios_base&)) {return *this;}
};

}

