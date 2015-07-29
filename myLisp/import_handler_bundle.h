#if ! defined(import_handler_bundle_h)
#define import_handler_bundle_h

    #include "import_handler.h"

    class ImportHandlerBundle : public ImportHandler {
        public:
            virtual std::string find_path(const std::string &name) override;
    };

#endif