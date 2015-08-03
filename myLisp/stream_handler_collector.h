#if ! defined(stream_handler_collector_h)
#define stream_handler_collector_h

    #include "stream_handler_str.h"

    #include <sstream>

    #include <AppKit/AppKit.h>

    class StreamHandlerCollector : public StreamHandlerStr {
        public:
            StreamHandlerCollector(NSMutableAttributedString *buffer, NSDictionary *dict):
                _buffer(buffer),
                _dict(dict)
            {}
        
            virtual std::string finish(std::ostream *stream) override;
        
        private:
            NSMutableAttributedString *_buffer;
            NSDictionary *_dict;
    };

#endif
