#include "../src/file_logger.h"
#include "../src/locking_actions.h"

#include <thread>
#include <string>
#include <vector>
#include <chrono>

using namespace log;
file_logger wl("testlog.log");

struct worker {

						worker(const std::string& _n, bool& _r):
		running(_r), name(_n) {

	}

	void 				work() {

		while(running) {

			log::lock(wl, lin::debug)<<"This is "<<name<<" saying debug"<<std::endl;
			log::lock(wl, lin::info)<<"This is "<<name<<" saying info"<<std::endl;
			log::lock(wl, lin::notice)<<"This is "<<name<<" saying notice"<<std::endl;
			log::lock(wl, lin::warning)<<"This is "<<name<<" saying warning"<<std::endl;
			log::lock(wl, lin::error)<<"This is "<<name<<" saying error"<<std::endl;
			log::lock(wl, lin::critical)<<"This is "<<name<<" saying critical"<<std::endl;
			log::lock(wl, lin::alert)<<"This is "<<name<<" saying alert"<<std::endl;
			log::lock(wl, lin::emergency)<<"This is "<<name<<" saying emergency"<<std::endl;
		}
	}

	bool&				running;
	std::string			name;
};

int main(int, char **) {

	bool running=true;

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


//TODO:
//	info(wl)<<"Fun will start ..."<<endl();
	std::vector<std::thread> threads;

	for(auto& w : workers) {
		threads.push_back(std::thread(&worker::work, std::ref(w)));
	}

	std::this_thread::sleep_for(std::chrono::seconds(2));
	running=false;

	for(auto& t : threads) {
		t.join();
	}

	return 0;
}
