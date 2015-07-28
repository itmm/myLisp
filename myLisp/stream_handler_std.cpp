#include "stream_handler_std.h"

std::ostream *StreamHandlerStd::prepare() { return &_stream; }

std::string StreamHandlerStd::finish(std::ostream *stream) {
    *stream << std::endl;
    stream->flush();
    return std::string();
}
