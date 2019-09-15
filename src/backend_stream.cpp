#include "backend_stream.h"

using namespace log;

backend_stream::backend_stream(std::ostream& _stream)
	:streamref(_stream) {

}

void backend_stream::commit(const std::string& _str) {

	streamref<<_str;
}
