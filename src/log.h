#ifndef TOOLS_LOG_H
#define TOOLS_LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <mutex>

namespace tools
{

//!Types of input.
enum class lin{error, warning, info, debug};

struct lcut {
					lcut(int _val):
		value(_val){
	}

	int				value;
};


//!Locking for threads.
struct llock{};
struct lunlock{};
struct lunlocknl{};
//!Time values.
enum class ltime{date, time, datetime};
//!Verbose tag output
enum class ltagout{verbose, silent};

//!A basic log to file.

//!The log allows for four levels (all, info, warning, error) of input, but
//!can be cut at any level to produce smaller files. It also has locking
//!capabilities for multithreading and date/time formats. Logs might be
//!inactive, on which case operations can be called upon them, but no logging
//!will happen.

class log
{
	public:

	//!This enum just bitwises the levels.
	enum levels{none=0, debug=1, info=2, warning=4, error=8, all=15};
	int lin_to_int(lin);

	//!Class constructor, creates an inactive log, with no file assigned.
	log();

	//!Class constructor, creates an active log, with a file assigned and opened.
	log(const char * filename);

	//!Class destructor. Adds a timestamp to the log file if possible (like deactivate).
	~log();

	//!Activates the log. Adds a timestamp to indicate that the session started.
	void activate();

	//!Dectivates the log. Adds a timestamp to indicate that the session ended.
	void deactivate();

	//!Opens the file. Returns true if the operation could be carried out, false if nothing happened. Used internally, but also used very specifically to close the handle and be able to rotate the logs in linux systems.
	bool open_file();

	//!Closes the file. Same as open_file.
	bool close_file();

	//!Inits the log, opening the file. Adds a timestamp to indicate that the session started.
	void init(const char * filename);

	//!Inserts data into the log.
	template <class X> log& operator<<(const X &input) {

		if(is_usable() && check_levels()) {
			s<<input;
			s.flush();
		}
		return *this;
	}

	//!Locks or unlocks the log for multithreading environments.

	//!In multithreaded environments, the log must be locked before writing
	//!and unlocked when done.
	log& operator<<(llock);
	log& operator<<(lunlock);
	log& operator<<(lunlocknl);

	//!Sets if the tag will be printed when changing levels.
	log& operator<<(ltagout);

	//!See the lin enum class for all possible input values.
	log& operator<<(lin);

	//!Sets the minimum level for the log to write data.

	//!Error will show only errors, warning will show errors and warnings, etc.
	log& operator<<(lcut);

	//!Adds the time, date or both to the output.

	//!See the ltime enum class for all possible input values.
	log& operator<<(ltime);

	//!Accepts std::ostream modifiers.
	log& operator<<(std::ostream& ( *pf )(std::ostream&));

	//!Accepts std::ios modifiers.
	log& operator<<(std::ios& ( *pf )(std::ios&));

	//!Accepts std::ios_base modifiers.
	log& operator<<(std::ios_base& ( *pf )(std::ios_base&));

	private:

	//!Checks if the current level can write.
	bool					check_levels() {return entry_level & allowed_levels;}
	bool					check_levels(int _lvl) {return _lvl & allowed_levels;}

	//!Indicates if the file is open and the log is active.
	bool 					is_usable() {return active && s.is_open();}

	//!Creates a string with the system date.
	std::string				date() const;

	//!Creates a string with the system time.
	std::string				time() const;

	std::mutex				mtx;		//!< Internal mutex for multithreaded logging.
	std::ofstream 			s;		//!< Internal output file stream.
	int 					entry_level=levels::all,	//!< Current log level.
							allowed_levels=levels::all;	//!< Current levels to warrant logging.
	bool 					active=false;		//!< Active flag.
	ltagout					tag_status=ltagout::verbose;

	friend					lunlock tools::endl(tools::log&);
	friend					log& tools::endln(tools::log&);
	friend					log& quick_log(tools::log&, lin);
};

}
#endif
