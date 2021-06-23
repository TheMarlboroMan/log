#include <lm/logger.h>

#include <stdexcept>

using namespace lm;

logger& logger::set_mask(int _mask) {

	if(levels::none==_mask || _mask > levels::all) {
		throw std::runtime_error("invalid mask value to logger::set_mask");
	}

	level_mask=_mask;
	return *this;
}

logger& logger::operator<<(lm::now) {

	if(!level_mask_ok) {
		return *this;
	}

	if(!format_time) {
		const size_t str_size=22;
		format_time=[](std::tm* _time) -> std::string {
			char * t=new char[str_size];
			memset(t, '\0', str_size);
			strftime(t, str_size, "%F %H:%M:%S", _time);
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

	return (*this)<<format_tag(_lvl);
}

