#pragma once

#include "logger.h"

#include "definitions.h"

#include <mutex>

namespace lm {

class locking_sentry;
class sentry;

//!Starts the locking chain with the given logger and a level. No other thread
//!will be able to call "lock" until this chain is done. The first version 
//!exists to guarantee backwards compatibility and it may be removed.
locking_sentry lock(logger&, lvl);
locking_sentry lock(logger&, manip_debug);
locking_sentry lock(logger&, manip_info);
locking_sentry lock(logger&, manip_notice);
locking_sentry lock(logger&, manip_warning);
locking_sentry lock(logger&, manip_error);
locking_sentry lock(logger&, manip_critical);
locking_sentry lock(logger&, manip_alert);
locking_sentry lock(logger&, manip_emergency);

//!Starts a log chain that will not lock the logger. The first version 
//!exists to guarantee backwards compatibility and it may be removed.
sentry log(logger&, lvl);
sentry log(logger&, manip_debug);
sentry log(logger&, manip_info);
sentry log(logger&, manip_notice);
sentry log(logger&, manip_warning);
sentry log(logger&, manip_error);
sentry log(logger&, manip_critical);
sentry log(logger&, manip_alert);
sentry log(logger&, manip_emergency);

//!log sentry interface, allows << operators to be written for both sentry types.
class log_sentry {

	public:
	virtual log_sentry& operator<<(const char * _val)=0;
	virtual log_sentry& operator<<(char _val)=0;
	virtual log_sentry& operator<<(int _val)=0;
	virtual log_sentry& operator<<(unsigned int _val)=0;
	virtual log_sentry& operator<<(long int _val)=0;
	virtual log_sentry& operator<<(long long int _val)=0;
	virtual log_sentry& operator<<(unsigned long int _val)=0;
	virtual log_sentry& operator<<(unsigned long long int _val)=0;
	virtual log_sentry& operator<<(double _val)=0;
	virtual log_sentry& operator<<(const std::string& _val)=0;
	virtual log_sentry& operator<<(std::ostream& (*pf)(std::ostream&))=0;
	virtual log_sentry& operator<<(std::ios& (*pf)(std::ios&))=0;
	virtual log_sentry& operator<<(std::ios_base& (*pf)(std::ios_base&))=0;
};

//!The locking sentry acts a log proxy that guarantees that a chain of insertion
//!operators will happen sequentially in the log thread, without other calls to
//!the same logger interfering.
class locking_sentry: public log_sentry{

	public:

	//!Class destructor. Public because once the chain ends, the scope
	//!needs to call this.
				~locking_sentry();

	locking_sentry& operator<<(const char * _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(char _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(unsigned int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(long long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(unsigned long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(unsigned long long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(double _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	locking_sentry& operator<<(const std::string& _val) {
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
	//
	//!Shared mutex for this part of the library...
	//TODO: Something interesting: different loggers should not share the same mutex
	static	std::mutex locking_sentry_mutex;


	friend locking_sentry   lock(logger&, lvl);
};

//!Proxy for the logger, non locking. The locking one could be implemented in
//!terms of this, to avoid duplication, but so far this is alright.
class sentry: public log_sentry {

	public:

	sentry& operator<<(const char * _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(char _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(unsigned int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(long long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(unsigned long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(unsigned long long int _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(double _val) {
		if(logger_instance.level_mask_ok) {
			logger_instance<<_val;
		}
		return *this;
	}
	sentry& operator<<(const std::string& _val) {
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
