#pragma once

#include "definitions.h"
#include "tools.h"

#include <functional>
#include <ctime>
#include <cstring>
#include <string>

namespace lm {

class locking_sentry;
class sentry;

//!Base class for all loggers. Defines a few methods common to all loggers
//!and the signatures for the logging methods proper.
class logger {

	public:

	//!Sets the tag format function, which must take a log::lvl and return
	//!a std::string. The function will be used each time a tag is printed
	//!to the log. Tags are "warning", "log", "critical", "debug" and so
	//!on.
	logger& set_tag_format(std::function<std::string(const lvl)> _func) {
	
		format_tag=_func;
		return *this;
	}

	//!Sets the time format function, which must take a pointer to a std::tm
	//!structure and return a std::string. The function will be used each
	//!time the log::now struct is sent into a logger, which is automatic
	//!when using the sentries (such as locking_sentry).
	logger& set_time_format(std::function<std::string(std::tm*)> _func) {
		
		format_time=_func;
		return *this;
	}

	//!Substitutes the current mask value for the one given. The mask value
	//!indicates which levels will be actually printed to the underlying
	//!log system.	
	logger& set_mask(int);

	//!Returns the current mask value.
	int get_mask() const {return level_mask;}
	protected:

	//!All insertion operators are protected so that only the sentries 
	//!access them.
	
	//!Insertion operator for a lm::now, which will format the current
	//!time according to the time format property of this class. A default
	//!function is provided.
	logger& operator<<(lm::now);

	//!Insertion operator for a lvl, which will format the passed tag
	//!using the tag format property of this class. A default function
	//!is provided.
	logger& operator<<(lvl);

	//!Stored function to format the tag name.
	std::function<std::string(const lvl)>		format_tag;

	//!Stored function to format the time.
	std::function<std::string(std::tm*)>		format_time;
	
	//!Level mask. When a message chain comes through, its level is checked
	//!against the mask and only comes through it the level value can be 
	//!and'ed with the mask.
	int level_mask=levels::all;

	//!Saves the state of the level mask against the current message chain
	//!so that the sentries can check if they must print or not.
	bool level_mask_ok=true;

	//!These are the regular insertion operators for printable types. Each
	//!derived class must specify the way in which data is managed.
	virtual logger& operator<<(const char *)=0;
	virtual logger& operator<<(char)=0;
	virtual logger& operator<<(int)=0;
	virtual logger& operator<<(unsigned int)=0;
	virtual logger& operator<<(long int)=0;
	virtual logger& operator<<(long long int)=0;
	virtual logger& operator<<(unsigned long int)=0;
	virtual logger& operator<<(unsigned long long int)=0;
	virtual logger& operator<<(double)=0;
	virtual logger& operator<<(const std::string&)=0;

	//!Accepts ostream modifiers.
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&))=0;
	
	//!Accepts ios modifiers.
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&))=0;

	//!Accepts ios_base modifiers.
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&))=0;	

	//!Allows sentries to access the internals of this class.
	friend class locking_sentry;
	friend class sentry;

	//!Allows the function that build sentries to access the 
	//!internals of this class.
	friend locking_sentry lock(logger&, lvl);
	friend sentry log(logger&, lvl);
};

}
