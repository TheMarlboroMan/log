#include <lm/ostream_logger.h>

using namespace lm;

ostream_logger::ostream_logger(std::ostream& _stream)
	:s(_stream){
}
