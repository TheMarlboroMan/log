//This example will use a file_logger: a log that writes to a file.
#include <lm/file_logger.h>

//In the example we will use locking sentries to use multiple threads writing
//to the same logger.
#include <lm/sentry.h>

#include <thread>
#include <string>
#include <vector>
#include <chrono>

using namespace lm;
//Initialise the file logger. This will open the file.
file_logger wl("testlog.log");

//For this example we will have N workers. Each worker will log for about two
//seconds without their data becoming corrupted or intertwined. The main thread
//will keep time and set the "running" flag to false, at which moment the 
//workers will stop logging when all messages in "work()" are issued.
struct worker {

						worker(const std::string& _n, bool& _r):
		running(_r), name(_n) {

	}

	void 				work() {

		while(running) {

//lm::lock receives a logger and a level. Once called, a "chain" is started. 
//The chain is used with the insertion operator and ends with the semicolon. As
//long as the chain has not ended, no other lm::lock calls will write to the
//logger.
			lm::lock(wl, lvl::debug)<<"This is "<<name<<" saying debug\n";
			lm::lock(wl, lvl::info)<<"This is "<<name<<" saying info\n";
			lm::lock(wl, lvl::notice)<<"This is "<<name<<" saying notice\n";
			lm::lock(wl, lvl::warning)<<"This is "<<name<<" saying warning\n";
			lm::lock(wl, lvl::error)<<"This is "<<name<<" saying error\n";
			lm::lock(wl, lvl::critical)<<"This is "<<name<<" saying critical\n";
			lm::lock(wl, lvl::alert)<<"This is "<<name<<" saying alert\n";
			lm::lock(wl, lvl::emergency)<<"This is "<<name<<" saying emergency"<<std::endl;
		}
	}

	const bool&				running;
	std::string			name;
};


int main(int, char **) {

	lm::file_logger fl("testlog.log");

	bool running=true;

	//Create all workers.
	std::vector<worker> workers{
		{"worker 1", running},
		{"worker 2", running},
		{"worker 3", running},
		{"worker 4", running},
		{"worker 5", running},
		{"worker 6", running},
		{"worker 7", running},
		{"worker 8", running},
		{"worker 9", running}
	};

	//!This is written without locks...
	lm::log(fl, lvl::info)<<"starting example"<<std::endl;
	
	std::vector<std::thread> threads;
	//Call "work" in each worker, so they start logging.
	for(auto& w : workers) {
		threads.push_back(std::thread(&worker::work, std::ref(w)));
	}

	//Sleep and stop the work.
	std::this_thread::sleep_for(std::chrono::seconds(2));
	running=false;

	//Wait for all workers to end.
	for(auto& t : threads) {
		t.join();
	}

	return 0;
}
