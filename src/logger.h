#pragma once

#include <functional>
#include <ctime>
#include <cstring>

#include "definitions.h"
#include "tools.h"

namespace log {

class locking_action;

//TODO: Document. It is NOT REALLY an interface, as it includes the format things.
class logger {

	public:

	//!Sets the tag format function, which must take a log::lin and return
	//!a std::string.
	logger& set_tag_format(std::function<std::string(const lin)> _func) {
	
		format_tag=_func;
		return *this;
	}

	//!Sets the time format function, which must take a pointer to a std::tm
	//!structure and return a std::string. 
	logger& set_time_format(std::function<std::string(std::tm*)> _func) {
		
		format_time=_func;
		return *this;
	}

	protected:

	//!All insertion operators are protected so that only the actions
	//!such as locking_action can access them.
	//TODO: Likely bullshit.
	logger& emergency() 	{return (*this)<<ltime{}<<" "<<lin::emergency;}
	logger& alert() 	{return (*this)<<ltime{}<<" "<<lin::alert;}
	logger& critical() 	{return (*this)<<ltime{}<<" "<<lin::critical;}
	logger& error() 	{return (*this)<<ltime{}<<" "<<lin::error;}
	logger& warning() 	{return (*this)<<ltime{}<<" "<<lin::warning;}
	logger& notice() 	{return (*this)<<ltime{}<<" "<<lin::notice;}
	logger& info() 		{return (*this)<<ltime{}<<" "<<lin::info;}
	logger& debug() 	{return (*this)<<ltime{}<<" "<<lin::debug;}

	//!Insertion operator for a ltime, which will format the current
	//!time according to the time format property of this class. A default
	//!function is provided.
	logger& operator<<(ltime);

	//!Insertion operator for a lin, which will format the passed tag
	//!using the tag format property of this class. A default function
	//!is provided.
	logger& operator<<(lin _lin);
 
	//TODO: Perhaps a better way of doing this would be just to mask the data
	//and have each operator in this class call a protected virtual function
	//that does the work...
	//!This is the operator for the cut level. 
	//TODO: Obviously, this motherfucker cannot be =0...
	//logger& operator<<(lcut)=0;

	//!Stored function to format the tag name.
	std::function<std::string(const lin)>		format_tag;

	//!Stored function to format the time.
	std::function<std::string(std::tm*)>		format_time;

	//!These are the regular insertion operators for printable types. Each
	//!derived class must specify the way in which data is managed.
	virtual logger& operator<<(const char *)=0;
	virtual logger& operator<<(int)=0;
	virtual logger& operator<<(double)=0;
	virtual logger& operator<<(const std::string&)=0;

	//!Accepts ostream modifiers.
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&))=0;
	
	//!Accepts ios modifiers.
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&))=0;

	//!Accepts ios_base modifiers.
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&))=0;	

	//!Allows locking_action to access the internals of this class.
	friend class locking_action;

	//!Allows the function that builds locking actions to access the 
	//!internals of this class.
	friend locking_action lock(logger&, lin);
};

}
