#ifndef TOOLS_LOG_H
#define TOOLS_LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "logger.h"

namespace log {

//!A basic log to file.

//!The log allows for all log levels of input, but can be cut at any level to 
//!produce smaller results.

class file_logger
	:public logger {
	public:
	
	//!Class constructor, creates an active log, with a file assigned and opened.
	file_logger(const char * filename);

	//!Class destructor. Adds a timestamp to the log file if possible (like deactivate).
	~file_logger();

	//TODO: These should also stamp the time and shit.

	logger& emergency() {
		return (*this)<<lin::emergency;
	}
	
	logger& alert() {
		return (*this)<<lin::alert;
	}

	logger& critical() {
		return (*this)<<lin::critical;
	}

	logger& error() {
		return (*this)<<lin::error;
	}

	logger& warning() {
		return (*this)<<lin::warning;
	}

	logger& notice() {
		return (*this)<<lin::notice;
	}

	logger& info() {
		return (*this)<<lin::info;
	}

	logger& debug() {
		return (*this)<<lin::debug;
	}

	virtual logger& operator<<(const char * _input) {return insert(_input);}
	virtual logger& operator<<(int _input) {return insert(_input);}
	virtual logger& operator<<(double _input) {return insert(_input);}
	virtual logger& operator<<(const std::string& _input) {return insert(_input);}
	
	//!Inserts data into the log. This is the interesting part, actually, the 
	//!one that allows us to use a fluent interface.
/* 	template <class X> 

	logger& operator<<(const X &input) {

		if(check_levels()) {
			s<<input;
			s.flush();
		}
		return *this;
	}
*/

	//!Sets if the tag will be printed when changing levels.
	logger& operator<<(ltagout);

	//!See the lin enum class for all possible input values.
	logger& operator<<(lin);

	//!Sets the minimum level for the log to write data.
	//!Error will show only errors, warning will show errors and warnings, etc.
	logger& operator<<(lcut);

	//!Adds the time, date or both to the output.
	//!See the ltime enum class for all possible input values.
	logger& operator<<(ltime);

	//!Accepts std::ostream modifiers.
	logger& operator<<(std::ostream& ( *pf )(std::ostream&));

	//!Accepts std::ios modifiers.
	logger& operator<<(std::ios& ( *pf )(std::ios&));

	//!Accepts std::ios_base modifiers.
	logger& operator<<(std::ios_base& ( *pf )(std::ios_base&));

	private:

	template<typename T>	
	logger&						insert(const T& _value) {

		if(check_levels()) {
			s<<_value;
			s.flush();
		}
		return *this;
	}

	//!Checks if the current level can write.
	bool					check_levels() const {return entry_level & allowed_levels;}
	bool					check_levels(int _lvl) const {return _lvl & allowed_levels;}

	std::string				filename;
	std::ofstream 			s;		//!< Internal output file stream.
	int 					entry_level=levels::all,	//!< Current log level.
							allowed_levels=levels::all;	//!< Current levels to warrant logging.	
	ltagout					tag_status=ltagout::verbose;};

}
#endif