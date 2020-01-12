#pragma once

#include <mutex>

#include "logger.h"
#include "definitions.h"

namespace log {

class locking_sentry;
class sentry;

//!Starts the locking chain with the given logger and a level. No other thread
//!will be able to call "lock" until this chain is done.
locking_sentry lock(logger&, lvl);

//!Starts a log chain that will not lock the logger.
sentry log(logger&, lvl);

//!Shared mutex for this part of the library...
//TODO: Something interesting: different loggers should not share the same mutex
std::mutex locking_sentry_mutex;

//!The locking sentry acts a log proxy that guarantees that a chain of insertion
//!operators will happen sequentially in the log thread, without other calls to
//!the same logger interfering.
class locking_sentry{

	public:

	//!Class destructor. Public because once the chain ends, the scope
	//!needs to call this.	
				~locking_sentry();

	//!Proxy for the logger: everything that goes in here enters the logger.
	template<typename X>
	locking_sentry& operator<<(const X& _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}

	//!Some magic for modifiers...
	locking_sentry& operator<<(std::ostream& (*pf)(std::ostream&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	locking_sentry& operator<<(std::ios& (*pf)(std::ios&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	locking_sentry& operator<<(std::ios_base& (*pf)(std::ios_base&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	private:
				locking_sentry(logger& _logger);

	logger&			logger_instance;
	
	friend locking_sentry   lock(logger&, lvl);
};

//!Proxy for the logger, non locking. The locking one could be implemented in
//!terms of this, to avoid duplication, but so far this is alright.
class sentry {

	public:

	//!Proxy for the logger: everything that goes in here enters the logger.
	template<typename X>
	sentry& operator<<(const X& _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}

	//!Some magic for modifiers...
	sentry& operator<<(std::ostream& (*pf)(std::ostream&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	sentry& operator<<(std::ios& (*pf)(std::ios&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	sentry& operator<<(std::ios_base& (*pf)(std::ios_base&)) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<pf;
		}
		return *this;
	}

	private:
				sentry(logger& _logger);

	logger&			logger_instance;
	
	friend sentry           log(logger&, lvl);

};
}
