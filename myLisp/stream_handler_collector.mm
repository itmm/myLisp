#include "stream_handler_collector.h"

std::string StreamHandlerCollector::finish(std::ostream *stream) {
    std::string result = StreamHandlerStr::finish(stream);
    NSAttributedString *formatted = [NSAttributedString.alloc
        initWithString: [NSString stringWithUTF8String: result.c_str()]
        attributes: _dict
    ];
    [_buffer appendAttributedString: formatted];
    [_buffer appendAttributedString: [NSAttributedString.alloc initWithString: @"\n"]];
    return std::string();
}
