#if ! defined(import_handler_h)
#define import_handler_h

    #include <string>
    #include <vector>

    class ImportHandler {
        public:
            virtual std::vector<std::string> find_paths(const std::string &name);
    };

#endif
