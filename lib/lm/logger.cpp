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

logger& logger::operator<<(lm::manip_now) {

	if(!level_mask_ok) {
		return *this;
	}

	if(!format_time) {
		const size_t str_size=22;
		format_time=[](std::tm* _time) -> std::string {
			char * t=new char[str_size];
			memset(t, '\0', str_size);
			strftime(t, str_size, "%Y-%m-%d %H:%M:%S", _time);
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

logger& logger::operator<<(manip_debug) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::debug);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::debug<<" ";
	return *this;
}

logger& logger::operator<<(manip_info) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::info);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::info<<" ";
	return *this;
}

logger& logger::operator<<(manip_notice) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::notice);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::notice<<" ";
	return *this;
}

logger& logger::operator<<(manip_warning) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::warning);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::warning<<" ";
	return *this;
}

logger& logger::operator<<(manip_error) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::error);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::error<<" ";
	return *this;
}

logger& logger::operator<<(manip_critical) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::critical);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::critical<<" ";
	return *this;
}

logger& logger::operator<<(manip_alert) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::alert);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::alert<<" ";
	return *this;
}

logger& logger::operator<<(manip_emergency) {

	level_mask_ok=level_mask & lvl_to_int(lm::lvl::emergency);
	if(!level_mask_ok) {

		return *this;
	}

	(*this)<<lm::now<<" "<<lm::lvl::emergency<<" ";
	return *this;
}
