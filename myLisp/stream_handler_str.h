#if ! defined(stream_handler_str_h)
#define stream_handler_str_h

    #include "stream_handler.h"

    #include <sstream>

    class StreamHandlerStr : public StreamHandler {
        public:
            StreamHandlerStr() {}

            virtual std::ostream *prepare() override;
            virtual std::string finish(std::ostream *stream) override;
    };
    
#endif
