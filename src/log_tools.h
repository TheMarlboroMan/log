#ifndef TOOLS_LOG_TOOLS_H
#define TOOLS_LOG_TOOLS_H

#include "log.h"

namespace tools {
//!Pairs of "lock" and "unlock" quick accesors: tools::error()<<"my stuff "<<errno<<tools::endl();
//!These also stamp the time.

log& emergency(tools::log&);
log& alert(tools::log&);
log& critical(tools::log&);
log& error(tools::log&);
log& warning(tools::log&);
log& notice(tools::log&);
log& info(tools::log&);
log& debug(tools::log&);

lunlocknl endl();
log& quick_log(tools::log&, tools::lin);
}

#endif
