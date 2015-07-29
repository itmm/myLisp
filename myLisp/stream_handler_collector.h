#if ! defined(stream_handler_collector_h)
#define stream_handler_collector_h

    #include "stream_handler_str.h"

    #include <sstream>

    #include <AppKit/AppKit.h>

    class StreamHandlerCollector : public StreamHandlerStr {
        public:
            StreamHandlerCollector(NSMutableAttributedString *buffer, NSColor *color): _buffer(buffer), _color(color) {}
        
            virtual std::string finish(std::ostream *stream) override;
        
        private:
            NSMutableAttributedString *_buffer;
            NSColor *_color;
    };

#endif
