#pragma once

namespace log {

//!Log levels, from the most critical to the least.
enum class lvl{emergency, alert, critical, error, warning, notice, info, debug};

//!Struct that represents the intention of logging the current time.
struct now{};

//!This enum just bitwises the levels.
enum levels{none=0, debug=1, info=2, notice=4, warning=8, error=16, critical=32, alert=64, emergency=128, all=255};
}
