#include "log.h"

using namespace tools;

lcut log::int_to_lcut(int _v) const {

	switch(_v) {
		case none: 		return lcut::none; break;
		case error: 	return lcut::error; break;
		case warning: 	return lcut::warning; break;
		case info: 		return lcut::info; break;
		case debug: 	return lcut::debug; break;
		case all: 		return lcut::all; break;
		default:
			throw std::runtime_error("Invalid cut level "+std::to_string(_v)+" specified for int_to_lcut");
		break;
	}

	//Compiler: just shut up.
	return lcut::all;
}

int	log::lcut_to_int(lcut _v) const {

	switch(_v) {
		case lcut::none: 	return none; break;
		case lcut::error: 	return error; break;
		case lcut::warning: return warning; break;
		case lcut::info: 	return info; break;
		case lcut::debug: 	return debug; break;
		case lcut::all: 	return all; break;
	}

	return all;
}

log::log()
	:s(), entry_level(levels::all), allowed_levels(levels::all),
	active(false) {

}

log::log(const char * filename)
	:s(), entry_level(levels::all), allowed_levels(levels::all),
	active(true) {

	init(filename);
}

log::~log() {

	if(is_usable()) {
		(*this)<<"Session ends "<<ltime::datetime<<std::endl;
		s.close();
	}
}

void log::activate() {
	active=true;
	if(is_usable()) {
		(*this)<<"Session starts "<<ltime::datetime<<std::endl;
	}
}

void log::deactivate() {

	if(is_usable())
	{
		(*this)<<"Session ends "<<ltime::datetime<<std::endl;
	}

	active=false;
}

void log::init(const char * filename) {
	s.open(filename);

	if(is_usable())
	{
		(*this)<<"Session starts "<<ltime::datetime<<std::endl;
	}
}

log& log::operator<<(lop op) {

	switch(op) {
		case lop::lock: 	mtx.lock(); break;
		case lop::unlock: 	mtx.unlock(); break;
	}
	return *this;
}

log& log::operator<<(lin lvl) {

	switch(lvl) {
		case lin::error:
			s<<"[ERROR] ";
			entry_level=error;
		break;
		case lin::warning:
			s<<"[WARNING] ";
			entry_level=warning;
		break;
		case lin::info:
			s<<"[INFO] ";
			entry_level=info;
		break;
		case lin::debug:
			s<<"[DEBUG] ";
			entry_level=debug;
		break;
	}
	return *this;
}

log& log::operator<<(lcut lvl) {

	switch(lvl) {
		case lcut::none: 	allowed_levels=none; break;
		case lcut::error: 	allowed_levels=error; break;
		case lcut::warning:	allowed_levels=warning; break;
		case lcut::info:	allowed_levels=info; break;
		case lcut::debug:	allowed_levels=debug; break;
		case lcut::all:		allowed_levels=all; break;
	}
	return *this;
}

log& log::operator<<(ltime v) {

	if(is_usable()) {
		switch(v) {
			case ltime::time:
				operator<<("[")<<time()<<"] ";
			break;
			case ltime::date:
				operator<<("[")<<date()<<"] ";
			break;
			case ltime::datetime:
				operator<<("[")<<date()<<" "<<time()<<"] ";
			break;
		}
	}

	return *this;
}

std::string log::time() const {
	/*TODO
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	out<<"\n"<<"0\n"<<std::put_time(&tm, "%H:%M:%S %d/%m/%Y");
	*/
	char * t=new char[14];
	memset(t, '\0', 14);
	time_t tiempo=std::time(nullptr);
	strftime(t, 14, "%H:%M:%S", localtime(&tiempo));
	std::string res(t);
	delete [] t ;
	return res;
}

//TODO: There are C++ ways of doing this.
std::string log::date() const {

	char * t=new char[14];
	memset(t, '\0', 14);
	time_t tiempo=std::time(nullptr);
	strftime(t, 14, "%Y-%m-%d", localtime(&tiempo));
	std::string res(t);
	delete [] t ;
	return res;
}

log& log::operator<<(std::ostream& ( *pf )(std::ostream&))
{
	if(is_usable() && check_levels()) {
		s<<pf;
	}
	return *this;
}

log& log::operator<<(std::ios& ( *pf )(std::ios&))
{
	if(is_usable() && check_levels())
	{
		s<<pf;
	}
	return *this;
}

log& log::operator<<(std::ios_base& ( *pf )(std::ios_base&))
{
	if(is_usable() && check_levels())
	{
		s<<pf;
	}
	return *this;
}
