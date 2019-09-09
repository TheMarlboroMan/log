#ifndef LOG_TOOLS_H
#define LOG_TOOLS_H

#include "definitions.h"

#include <string>

namespace log {

int lin_to_int(lin);

//!Creates a string with the system date.
std::string	date();

//!Creates a string with the system time.
std::string time();

const char * lin_to_tag(lin);
}

#endif