#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "logger.h"

namespace log {


//!A basic log to file.

class file_logger
	:public logger {
	public:
	
	//!Class constructor, creates an active log, with a file assigned and opened.
	file_logger(const char * filename);

	//!Class destructor. Adds a timestamp to the log file if possible (like deactivate).
	~file_logger();

	protected:

	//!This begins the implementation of the base class.
	virtual logger& operator<<(const char * _input) {return insert(_input);}
	virtual logger& operator<<(int _input) {return insert(_input);}
	virtual logger& operator<<(double _input) {return insert(_input);}
	virtual logger& operator<<(const std::string& _input) {return insert(_input);}
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&)) {return insert(pf);}
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&)) {return insert(pf);}
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&)) {return insert(pf);}

	private:

	template<typename T>	
	logger&						insert(const T& _value) {

		s<<_value;
		s.flush();
		return *this;
	}

	std::string				filename;
	std::ofstream 			s;		//!< Internal output file stream.
};

}
