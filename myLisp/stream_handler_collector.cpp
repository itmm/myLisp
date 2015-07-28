#include "stream_handler_collector.h"

std::string StreamHandlerCollector::finish(std::ostream *stream) {
    std::string result = StreamHandlerStr::finish(stream);
    buffer << result << std::endl;
    return std::string();
}
