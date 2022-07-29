#include <lm/log.h>

#include <iostream>

using namespace lm;

std::mutex log::locking_sentry_mutex;
