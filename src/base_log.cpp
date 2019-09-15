#include "base_log.h"

#include "sentry.h"
#include "tools.h"

using namespace log;

void base_log::commit(const std::string& _str) {

	std::lock_guard<std::mutex> lock{mtx};
	get_backend().commit(_str);
}
