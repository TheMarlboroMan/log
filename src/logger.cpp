#include "logger.h"

using namespace log;

logger& logger::operator<<(ltime) {

	if(!format_time) {
		const size_t str_size=22;
		format_time=[](std::tm* _time) -> std::string {
			char * t=new char[str_size];
			memset(t, '\0', str_size);
			strftime(t, str_size, "%F %T", _time);
			std::string res(t);
			delete [] t;
			return std::string("(")+res+")";
		};
	}

	time_t time=std::time(nullptr);
	auto t_struct=std::localtime(&time);
	return (*this)<<format_time(t_struct);
}

logger& logger::operator<<(lin _lin) {

	if(!format_tag) {
		format_tag=[](const lin _tag) -> std::string {
			switch(_tag) {
				case lin::emergency: return "[emergency]";
				case lin::alert:     return "[alert]";
				case lin::critical:  return "[critical]";
				case lin::error:     return "[error]";
				case lin::warning:   return "[warning]";
				case lin::notice:    return "[notice]";
				case lin::info:      return "[info]";
				case lin::debug:     return "[debug]";
			}
			return "[???]";
		};
	}
	
	return (*this)<<format_tag(_lin);
}

