#if ! defined(stream_handler_collector_h)
#define stream_handler_collector_h

    #include "stream_handler_str.h"

    #include <sstream>

    class StreamHandlerCollector : public StreamHandlerStr {
        public:
            std::string str() { return buffer.str(); }
            void str(const std::string &s) { buffer.str(s); }

            virtual std::string finish(std::ostream *stream) override;
        
        private:
            std::ostringstream buffer;
    };

#endif
