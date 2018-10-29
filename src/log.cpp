#include "log.h"

using namespace tools;

log::log()
	:s() {

}

log::log(const char * filename)
	:s() {

	init(filename);
	active=true;
}

log::~log() {

	if(is_usable()) {
		(*this)<<ltime::datetime<<"Session ends"<<std::endl;
		s.close();
	}
}

void log::activate() {
	active=true;
	if(is_usable()) {
		(*this)<<ltime::datetime<<"Session starts "<<std::endl;
	}
}

void log::deactivate() {

	if(is_usable()) {
		(*this)<<ltime::datetime<<"Session ends "<<std::endl;
	}

	active=false;
}

void log::init(const char * filename) {
	s.open(filename);

	if(is_usable())	{
		(*this)<<ltime::datetime<<"Session starts "<<std::endl;
	}
}

log& log::operator<<(llock) {

	mtx.lock();
	return *this;
}

log& log::operator<<(lunlock) {

	mtx.unlock();
	return *this;
}

log& log::operator<<(lunlocknl) {

	*this<<std::endl;
	mtx.unlock();
	return *this;
}

int log::lin_to_int(lin _lin) {

	switch(_lin) {
		case lin::error:	return levels::error;
		case lin::warning:	return levels::warning;
		case lin::info:		return levels::info;
		case lin::debug:	return levels::debug;
	}

	return levels::all;
}

//TODO: How could we enable silent mode???
log& log::operator<<(lin _lvl) {

	std::string tag;

	switch(_lvl) {
		case lin::error:
			entry_level=error;
			tag="[ERROR] ";
		break;
		case lin::warning:
			entry_level=warning;
			tag="[WARNING] ";
		break;
		case lin::info:
			entry_level=info;
			tag="[INFO] ";
		break;
		case lin::debug:
			entry_level=debug;
			tag="[DEBUG] ";
		break;
	}

	if(tag_status==ltagout::verbose && check_levels(lin_to_int(_lvl))) {
		s<<tag;
	}

	return *this;
}

log& log::operator<<(ltagout _lt) {

	tag_status=_lt;
	return *this;
}

log& log::operator<<(lcut _lcut) {

	allowed_levels=_lcut.value;
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
