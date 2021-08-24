#pragma once

namespace lm {

//!Log levels, from the most critical to the least.
enum class lvl{emergency, alert, critical, error, warning, notice, info, debug};

//!Struct that represents the intention of logging the current time. Instanced
//!as now and exported to the outside world.
struct manip_now{};
extern manip_now now;

//!Representing the intention of logging the current time, plus a level.
struct manip_debug{};
struct manip_info{};
struct manip_notice{};
struct manip_warning{};
struct manip_error{};
struct manip_critical{};
struct manip_alert{};
struct manip_emergency{};

extern manip_debug debug;
extern manip_info info;
extern manip_notice notice;
extern manip_warning warning;
extern manip_error error;
extern manip_critical critical;
extern manip_alert alert;
extern manip_emergency emergency;

//!This struct just bitwises the levels, used for masks.
struct levels{
	static const int none=0;
	static const int debug=1;
	static const int info=2;
	static const int notice=4; 
	static const int warning=8;
	static const int error=16;
	static const int critical=32;
	static const int alert=64;
	static const int emergency=128;
	static const int all=255;
};
}
