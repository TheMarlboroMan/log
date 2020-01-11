#include "ostream_logger.h"

using namespace log;

ostream_logger::ostream_logger(std::ostream& _stream)
	:s(_stream){
}
