#include "import_handler.h"

std::vector<std::string> ImportHandler::find_paths(const std::string &name) {
    std::vector<std::string> result;
    result.push_back(name);
    return result;
}
