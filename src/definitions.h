#pragma once

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
struct ltime{};

//!This enum just bitwises the levels.
enum levels{none=0, debug=1, info=2, notice=4, warning=8, error=16, critical=32, alert=64, emergency=128, all=255};

}
