#pragma once

#include <functional>
#include <ctime>

#include "definitions.h"
#include "tools.h"

namespace log {

//TODO: Document. It is NOT REALLY an interface, as it includes the format things.
class logger {

	public:

	//TODO: Document.

	//TODO: Part of this code is repeated in "locking actions, which is absurd".
	//TODO: Bad, why did you choose datetime for me????

	logger& emergency() {return (*this)<<ltime::datetime<<lin::emergency;}
	logger& alert() 	{return (*this)<<ltime::datetime<<lin::alert;}
	logger& critical() 	{return (*this)<<ltime::datetime<<lin::critical;}
	logger& error() 	{return (*this)<<ltime::datetime<<lin::error;}
	logger& warning() 	{return (*this)<<ltime::datetime<<lin::warning;}
	logger& notice() 	{return (*this)<<ltime::datetime<<lin::notice;}
	logger& info() 		{return (*this)<<ltime::datetime<<lin::info;}
	logger& debug() 	{return (*this)<<ltime::datetime<<lin::debug;}

	logger& operator<<(ltime) {

		//TODO: Bullshit, it should get decltype of localtime, * std::tm, 
		//which should be provided by this method.



		if(!format_time) {
			format_time=[](std::tm* _time) -> std::string {
//		strftime(t, 14, "%H:%M:%S", );
				return std::string("(")+_time+")";
			};
		}

		time_t time=std::time(nullptr);


		return (*this)<<format_time(localtime(&time));
	}

	logger& operator<<(lin) {
		if(!format_tag) {
			format_tag=[](const std::string& _tag) -> std:string {
				return std::string("[")+_tag+"]";
			};
		}

		return (*this)<<format_tag(lin_to_tag(_lvl));
	}


	virtual logger& operator<<(const char *)=0;
	virtual logger& operator<<(int)=0;
	virtual logger& operator<<(double)=0;
	virtual logger& operator<<(const std::string&)=0;

	virtual logger& operator<<(lcut)=0;
	virtual logger& operator<<(std::ostream& ( *pf )(std::ostream&))=0;
	virtual logger& operator<<(std::ios& ( *pf )(std::ios&))=0;
	virtual logger& operator<<(std::ios_base& ( *pf )(std::ios_base&))=0;


	private:

	std::function<std::string(const std::string)>	format_time,
											format_tag;
};

}
