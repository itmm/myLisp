#include "stream_handler_str.h"

std::ostream *StreamHandlerStr::prepare() {
    return new std::ostringstream();
}

std::string StreamHandlerStr::finish(std::ostream *stream) {
    stream->flush();
    std::string result = dynamic_cast<std::ostringstream *>(stream)->str();
    delete stream;
    return result;
}
