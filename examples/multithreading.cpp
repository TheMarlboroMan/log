#include "../src/log.h"
#include "../src/log_tools.h"

#include <thread>
#include <string>
#include <vector>
#include <chrono>

using namespace tools;
log wl("testlog.log");

struct worker {

						worker(const std::string& _n, bool& _r):
		running(_r), name(_n) {

	}

	void 				work() {

		while(running) {
			tools::debug(wl)<<"This is "<<name<<" saying debug"<<tools::endl();
			tools::info(wl)<<"This is "<<name<<" saying info"<<tools::endl();
			tools::notice(wl)<<"This is "<<name<<" saying notice"<<tools::endl();
			tools::warning(wl)<<"This is "<<name<<" saying warning"<<tools::endl();
			tools::error(wl)<<"This is "<<name<<" saying error"<<tools::endl();
			tools::critical(wl)<<"This is "<<name<<" saying critical"<<tools::endl();
			tools::alert(wl)<<"This is "<<name<<" saying alert"<<tools::endl();
			tools::emergency(wl)<<"This is "<<name<<" saying emergency"<<tools::endl();
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


	tools::info(wl)<<"Fun will start ..."<<tools::endl();
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

/*
int main(int, char**) {

	using namespace tools;

	log l("testlog.log");

	l<<lcut(log::info | log::error)
		<<lin::debug<<"THIS DEBUG SHOULD NOT BE PRINTED"<<std::endl
		<<lin::warning<<"THIS WARNING SHOULD NOT BE PRINTED"<<std::endl
		<<lin::info<<"THIS INFO SHOULD BE PRINTED"<<std::endl
		<<lin::error<<"THIS ERROR SHOULD BE PRINTED"<<std::endl;

	l<<lcut(log::all)<<"-------- DONE WITH THE FIRST ROUND OF TESTS"
		<<lcut(log::info | log::error);

	debug(l)<<"THIS LOCKED DEBUG SHOULD NOT BE PRINTED"<<endl(l);
	info(l)<<"THIS LOCKED INFO SHOULD BE PRINTED"<<endl(l);
	error(l)<<"THIS LOCKED ERROR SHOULD BE PRINTED"<<endl(l);
	warning(l)<<"THIS LOCKED WARNING SHOULD NOT BE PRINTED"<<endl(l);


	return 1;

}
*/