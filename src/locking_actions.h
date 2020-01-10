#ifndef TOOLS_LOCKING_ACTIONS_H
#define TOOLS_LOCKING_ACTIONS_H

#include <mutex>

#include "logger.h"
#include "definitions.h"

namespace log {

class locking_action;
//TODO: Document.
locking_action lock(logger& _logger);
locking_action lock(logger&, lin);

//!Shared mutex for this part of the library...
std::mutex locking_actions_mutex;

//TODO: This should actually be something like the "log_sentry"
//TODO: Perhaps we could have many independent sentries, and a mutex in the
//message method of the log... That sounds like a reasonable implementation
//that would allow for different threads to work at the same time.

/*
This is sent by a log upon call to their stuff, and acts as a buffer too. 
Stores the moment when the log call was invoked, but in multithreading environ-
ments may end up being saved AFTER previous calls.

class log_sentry {

	template<typename X>
	log_sentry&			operator<<(const X& _val) {
		buffer<<_val;
		return this;
	}

						log_sentry(logger& _logger, level)
			:logger{_logger}, lvl{_level}, moment{lalalal} {
			
	}
						~log_sentry() {
		logger_instance.message(buffer.str(), lvl, moment);
	}

	now					moment;
	level				lvl
	std::sstream		buffer;
	std::logger&		logger_instance;
}


class logger {
	void message(const std::string& _msg) {
		std::lock_guard<std::mutex> lock{mtx};
		us->commit(_msg);
	}

	std::unique_ptr<underlying_stream> us;
}

underlying stream should be something like:
class underlying_stream {
	public:	
	virtual void commit(const std::string& _msg)=0;
};

Which then goes like:
class output_stream
	:public underlying_stream
	public:
		underlying_stream(std::ostream& _stream):
			stream(_stream) {
				
	}

	void commit(const std:.string& _msg) {
		stream<<_msg;
	}	

	std::ostream& stream;
};

class void_stream
	:public underlying_stream
	public:
	void commit(const std:.string& _msg) {}	
};

All that would be left would be out logger specializations that build their own
underlying streams as std::ofstream, std::cout, std::cerr or void_stream.
It's also nice in that all code that deals with log templates and things can be
in the base class...
*/

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
