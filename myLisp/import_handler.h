#if ! defined(import_handler_h)
#define import_handler_h

    #include <string>

    class ImportHandler {
        public:
            virtual std::string find_path(const std::string &name);
    };

#endif
