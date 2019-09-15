#include "../src/file_logger.h"
#include "../src/mute_logger.h"

#include <thread>
#include <string>
#include <vector>
#include <chrono>

using namespace log;

struct worker {

						worker(const std::string& _n, bool& _r, log::base_log& _log):
		running(_r), name(_n), log{_log} {

	}

	void 				work() {

		while(running) {

			log.debug()<<"This is "<<name<<" saying debug"<<std::endl;
			log.info()<<"This is "<<name<<" saying info"<<std::endl;
			log.notice()<<"This is "<<name<<" saying notice"<<std::endl;
			log.warning()<<"This is "<<name<<" saying warning"<<std::endl;
			log.error()<<"This is "<<name<<" saying error"<<std::endl;
			log.critical()<<"This is "<<name<<" saying critical"<<std::endl;
			log.alert()<<"This is "<<name<<" saying alert"<<std::endl;
			log.emergency()<<"This is "<<name<<" saying emergency"<<std::endl;
		}
	}

	bool&				running;
	std::string			name;
	//TODO: Actually, rename it...
	log::base_log&		log;
};

void screamer(bool& running, log::base_log& _log);

int main(int, char **) {

	log::file_logger fl("testlog.log");
	log::mute_logger ml;

	bool running=true;

	std::vector<worker> workers{
		{"worker 1", running, fl},
		{"worker 2", running, fl},
		{"worker 3", running, fl},
		{"worker 4", running, fl},
		{"worker 5", running, fl},
		{"worker 6", running, fl},
		{"worker 7", running, fl},
		{"worker 8", running, fl},
		{"worker 9", running, fl}
	};

	std::cout<<"Fun will start ..."<<std::endl;
	std::vector<std::thread> threads;

	for(auto& w : workers) {
		threads.push_back(std::thread(&worker::work, std::ref(w)));
	}

	std::thread screamthread{screamer, std::ref(running), std::ref(ml)};

	std::cout<<"Sleep for two seconds..."<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout<<"Sleep for one second..."<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout<<"Joining threads..."<<std::endl;
	running=false;

	for(auto& t : threads) {
		t.join();
	}
	screamthread.join();

	return 0;
}

void screamer(bool& running, log::base_log& _log) {

	while(running) {
		_log.emergency()<<"SCREAM!!!"<<std::endl;
	}
}
