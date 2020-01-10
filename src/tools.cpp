#include "tools.h"

#include <ctime>
#include <cstring>

using namespace log;

int log::lin_to_int(lin _lin) {

	switch(_lin) {
		case lin::emergency:	return levels::emergency;
		case lin::alert:		return levels::alert;
		case lin::critical:		return levels::critical;
		case lin::error:		return levels::error;
		case lin::warning:		return levels::warning;
		case lin::notice:		return levels::notice;
		case lin::info:			return levels::info;
		case lin::debug:		return levels::debug;
	}

	return levels::all;
}

const char * log::lin_to_tag(lin _lin) {

	switch(_lin) {
		case lin::emergency:	return "emergency";
		case lin::alert:		return "alert";
		case lin::critical:		return "critical";
		case lin::error:		return "error";
		case lin::warning:		return "warning";
		case lin::notice:		return "notice";
		case lin::info:			return "info";
		case lin::debug:		return "debug";
	}

	return "???";
}
/*
TODO: Erase this when the time comes...
std::string log::ldate_to_str(ltime _val, ltime _default) {

	switch(_val) {
		case ltime::time:		return time();
		case ltime::date:		return date();
		case ltime::datetime: 	return date()+" "+time();
		case ltime::none:		return std::string();
		case ltime::def:		return ldate_to_str(_default, _default);
	}
}
*/
std::string log::time() {
	/*TODO
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	out<<"\n"<<"0\n"<<std::put_time(&tm, "%H:%M:%S %d/%m/%Y");
	*/
	char * t=new char[14];
	memset(t, '\0', 14);
	time_t tiempo=std::time(nullptr);
	strftime(t, 14, "%H:%M:%S", localtime(&tiempo));
	std::string res(t);
	delete [] t ;
	return res;
}

//TODO: There are C++ ways of doing this.
std::string log::date() {

	char * t=new char[14];
	memset(t, '\0', 14);
	time_t tiempo=std::time(nullptr);
	strftime(t, 14, "%Y-%m-%d", localtime(&tiempo));
	std::string res(t);
	delete [] t ;
	return res;
}


