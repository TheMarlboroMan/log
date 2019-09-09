#ifndef TOOLS_LOCKING_ACTIONS_H
#define TOOLS_LOCKING_ACTIONS_H

#include <mutex>

#include "logger.h"
#include "definitions.h"

namespace log {

class locking_action;
//TODO: Document.
locking_action lock(logger& _logger);

//!Shared mutex for this part of the library...
std::mutex locking_actions_mutex;

//TODO: Document...
class locking_action {

	public:

	//TODO: Document.
									locking_action(logger& _logger);
									~locking_action();

	//TODO: Document.			
	template<typename X>
	logger&							operator<<(const X& _val) {
		return logger_instance<<_val;
	}

	private:
	
	logger&							logger_instance;
};

//!Pairs of "lock" and "unlock" quick accesors: tools::error()<<"my stuff "<<errno<<std::endl;
//!These also stamp the time.
/*
logger& emergency(logger&);
logger& alert(logger&);
logger& critical(logger&);
logger& error(logger&);
logger& warning(logger&);
logger& notice(logger&);
logger& info(logger&);
logger& debug(logger&);

lunlocknl endl();
logger& quick_log(logger&, lin);
*/
}

#endif
