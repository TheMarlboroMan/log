#ifndef LOG_LOGGER_INTERFACE_H
#define LOG_LOGGER_INTERFACE_H

#include "definitions.h"

namespace log {

//TODO: Document.
class logger {

	public:

	//TODO: Document.
	//TODO: Kind of makes you wonder if this does really make any sense...
	virtual logger& emergency()=0;
	virtual logger& alert()=0;
	virtual logger& critical()=0;
	virtual logger& error()=0;
	virtual logger& warning()=0;
	virtual logger& notice()=0;
	virtual logger& info()=0;
	virtual logger& debug()=0;
	virtual logger& operator<<(const char *)=0;
	virtual logger& operator<<(int)=0;
	virtual logger& operator<<(double)=0;
	virtual logger& operator<<(const std::string&)=0;
	virtual logger& operator<<(lin)=0;	
	virtual logger& operator<<(ltagout)=0;
	virtual logger& operator<<(lcut)=0;
	virtual logger& operator<<(ltime)=0;
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&))=0;
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&))=0;
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&))=0;
};

}

#endif