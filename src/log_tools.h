#ifndef TOOLS_LOG_TOOLS_H
#define TOOLS_LOG_TOOLS_H

#include "log.h"

namespace tools {
//!Pairs of "lock" and "unlock" quick accesors: tools::error()<<"my stuff "<<errno<<tools::endl();
//!These also stamp the time.

log& error(tools::log& srvlog);
log& warning(tools::log& srvlog);
log& info(tools::log& srvlog);
log& debug(tools::log& srvlog);
void endl(tools::log& srvlog);
}

#endif
