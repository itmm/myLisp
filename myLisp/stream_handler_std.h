#if ! defined(stream_handler_std_h)
#define stream_handler_std_h

    #include "stream_handler.h"

    class StreamHandlerStd : public StreamHandler {
        public:
            StreamHandlerStd(std::ostream &stream): _stream(stream) {}

            virtual std::ostream *prepare() override;
            virtual std::string finish(std::ostream *stream) override;
        
        private:
            std::ostream &_stream;
    };

#endif
