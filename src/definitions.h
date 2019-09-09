#ifndef LOG_DEFINITIONS_H
#define LOG_DEFINITIONS_H

namespace log {

//!Types of input.
enum class lin{emergency, alert, critical, error, warning, notice, info, debug};

struct lcut {
					lcut(int _val):
		value(_val){
	}

	int				value;
};

//!Time values.
enum class ltime{date, time, datetime};
//!Verbose tag output
enum class ltagout{verbose, silent};

//!This enum just bitwises the levels.
enum levels{none=0, debug=1, info=2, notice=4, warning=8, error=16, critical=32, alert=64, emergency=128, all=255};

}

#endif