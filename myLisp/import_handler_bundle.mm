#include "import_handler_bundle.h"

#import <Foundation/Foundation.h>

std::vector<std::string> ImportHandlerBundle::find_paths(const std::string &name) {
    NSString *str = [NSString stringWithUTF8String: name.c_str()];
    NSString *path = [NSBundle.mainBundle pathForResource: str.stringByDeletingPathExtension ofType: str.pathExtension];
    if (path) {
        std::vector<std::string> result;
        result.push_back(path.UTF8String);
        return result;
    } else {
        return ImportHandler::find_paths(name);
    }
}
