#if ! defined(stream_handler_h)
#define stream_handler_h

    #include "ptr.h"

    #include <string>

    class StreamHandler {
        public:
            StreamHandler() {}
            virtual ~StreamHandler();
        
            virtual std::ostream *prepare() = 0;
            virtual std::string finish(std::ostream *stream);
        
        private:
            StreamHandler(const StreamHandler &) = delete;
            StreamHandler &operator=(const StreamHandler &) = delete;
    };

#endif
