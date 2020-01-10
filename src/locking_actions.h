#pragma once

#include <mutex>

#include "logger.h"
#include "definitions.h"

namespace log {

class locking_action;

//!Starts the locking chain with the given logger and a level. No other thread
//!will be able to call "lock" until this chain is done.
locking_action lock(logger&, lin);

//!Shared mutex for this part of the library...
//TODO: Something interesting: different loggers should not share the same mutex
std::mutex locking_actions_mutex;

//!The locking action acts a log proxy that guarantees that a chain of insertion
//!operators will happen sequentially in the log thread, without other calls to
//!the same logger interfering.
class locking_action {

	public:

	//!Class destructor. Public because once the chain ends, the scope
	//!needs to call this.	
				~locking_action();

	//!Proxy for the logger: everything that goes in here enters the logger.
	template<typename X>
	locking_action& operator<<(const X& _val) {
		logger_instance<<_val;
		return *this;
	}

	private:
				locking_action(logger& _logger);

	logger&			logger_instance;
	
	friend locking_action   lock(logger&, lin);
};
}
