#include "logger.h"

using namespace log;

logger& logger::set_mask(int _mask) {

	//TODO: We should actually check that the value is valid, that
	//is, it is not levels::none and it is not larger than levels::all
	level_mask=_mask;
	return *this;
}

logger& logger::operator<<(log::now) {

	if(!level_mask_ok) {
		return *this;
	}

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

logger& logger::operator<<(lvl _lvl) {

	level_mask_ok=level_mask & lvl_to_int(_lvl);
	if(!level_mask_ok) {

		return *this;
	}

	if(!format_tag) {
		format_tag=[](const lvl _tag) -> std::string {
			switch(_tag) {
				case lvl::emergency: return "[emergency]";
				case lvl::alert:     return "[alert]";
				case lvl::critical:  return "[critical]";
				case lvl::error:     return "[error]";
				case lvl::warning:   return "[warning]";
				case lvl::notice:    return "[notice]";
				case lvl::info:      return "[info]";
				case lvl::debug:     return "[debug]";
			}
			return "[???]";
		};
	}

//TODO: Perhaps we should check the level here. If the level does not match
//the mask we could return false. The sentries could use that result to return
//a null sentry, which would just do nothing. Easier would be to have a 
//level_allowed boolean, set it here, use it in the sentries. Go to hell.	
	return (*this)<<format_tag(_lvl);
}

