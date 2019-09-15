#ifndef LOG_BASE_LOG_H
#define LOG_BASE_LOG_H

#include <string>
#include <mutex>

#include "sentry.h"
#include "backend.h"
#include "definitions.h"

namespace log {

class sentry;

//!Base for all log classes. Specifically designed to be extended in the 
//!get_stream method, which must return the underlying stream for the given
//!type.
class base_log {

	public:
								~base_log() {}

	sentry						debug() {return sentry{*this, lin::debug};}
	sentry						info() {return sentry{*this, lin::info};}
	sentry						notice() {return sentry{*this, lin::notice};}
	sentry						warning() {return sentry{*this, lin::warning};}
	sentry						error() {return sentry{*this, lin::error};}
	sentry						critical() {return sentry{*this, lin::critical};}
	sentry						alert() {return sentry{*this, lin::alert};}
	sentry						emergency() {return sentry{*this, lin::emergency};}

	//!Logs the string to file. For internal use, will be called by the log
	//!sentries, should not be called directly.
	void						commit(const std::string&);

	protected:

	virtual backend&			get_backend()=0;

	private:

	std::mutex					mtx;
};

}

#endif
