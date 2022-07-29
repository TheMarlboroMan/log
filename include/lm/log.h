#pragma once

#include "logger.h"

#include "definitions.h"

#include <mutex>
#include <stdexcept>

namespace lm {

class log {

	public:

	log(logger& _logger):internal_logger{_logger} {}
	~log() {

		if(locked) {

			unlock();
		}
	}

	log& lock() {

		locking_sentry_mutex.lock();
		locked=true;
		return *this;
	}

	log& unlock() {

		locking_sentry_mutex.unlock();
		locked=false;
		return *this;
	}

	log& debug() {internal_logger<<lm::now<<" "<<lm::lvl::debug<<" "; return *this;}
	log& info() {internal_logger<<lm::now<<" "<<lm::lvl::info<<" "; return *this;}
	log& notice() {internal_logger<<lm::now<<" "<<lm::lvl::notice<<" "; return *this;}
	log& warning() {internal_logger<<lm::now<<" "<<lm::lvl::warning<<" "; return *this;}
	log& error() {internal_logger<<lm::now<<" "<<lm::lvl::error<<" "; return *this;}
	log& critical() {internal_logger<<lm::now<<" "<<lm::lvl::critical<<" "; return *this;}
	log& alert() {internal_logger<<lm::now<<" "<<lm::lvl::alert<<" "; return *this;}
	log& emergency() {internal_logger<<lm::now<<" "<<lm::lvl::emergency<<" "; return *this;}

	log& operator<<(const char * _val) {internal_logger<<_val; return *this;}
	log& operator<<(char _val) {internal_logger<<_val; return *this;}
	log& operator<<(int _val) {internal_logger<<_val; return *this;}
	log& operator<<(unsigned int _val) {internal_logger<<_val; return *this;}
	log& operator<<(long int _val) {internal_logger<<_val; return *this;}
	log& operator<<(long long int _val) {internal_logger<<_val; return *this;}
	log& operator<<(unsigned long int _val) {internal_logger<<_val; return *this;}
	log& operator<<(unsigned long long int _val) {internal_logger<<_val; return *this;}
	log& operator<<(double _val) {internal_logger<<_val; return *this;}
	log& operator<<(const std::string& _val) {internal_logger<<_val; return *this;}
	log& operator<<(std::ostream& (*pf)(std::ostream&)) {internal_logger<<pf; return *this;}
	log& operator<<(std::ios& (*pf)(std::ios&)) {internal_logger<<pf; return *this;}
	log& operator<<(std::ios_base& (*pf)(std::ios_base&)) {internal_logger<<pf; return *this;}

	private:

	lm::logger& internal_logger;
	static std::mutex locking_sentry_mutex;
	bool locked{false};
};

}
