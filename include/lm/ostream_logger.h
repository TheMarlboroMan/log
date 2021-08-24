#pragma once

#include "logger.h"

#include <ostream>
#include <string>
#include <sstream>

namespace lm {


//!A log to an output stream.
class ostream_logger
	:public logger {
	public:
	
	//!Class constructor, creates an active log, with a file assigned and opened.
	ostream_logger(std::ostream&);
	
#ifndef OPEN_LOG_OPERATORS
	protected:
#endif

	//!This begins the implementation of the base class.
	virtual logger& operator<<(const char * _input) {return insert(_input);}
	virtual logger& operator<<(char _input) {return insert(_input);}
	virtual logger& operator<<(int _input) {return insert(_input);}
	virtual logger& operator<<(unsigned int _input) {return insert(_input);}
	virtual logger& operator<<(long int _input) {return insert(_input);}
	virtual logger& operator<<(unsigned long int _input) {return insert(_input);}
	virtual logger& operator<<(long long int _input) {return insert(_input);}
	virtual logger& operator<<(unsigned long long int _input) {return insert(_input);}
	virtual logger& operator<<(double _input) {return insert(_input);}
	virtual logger& operator<<(const std::string& _input) {return insert(_input);}
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&)) {return insert(pf);}
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&)) {return insert(pf);}
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&)) {return insert(pf);}

	private:

	template<typename T>	
	logger&						insert(const T& _value) {

		if(!level_mask_ok) {

			return *this;
		}

		s<<_value;
		s.flush();
		return *this;
	}

	std::ostream& 			s; //!<Internal output stream.
};

}
