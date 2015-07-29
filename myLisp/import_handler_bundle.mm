#include "import_handler_bundle.h"

#import <Foundation/Foundation.h>

std::string ImportHandlerBundle::find_path(const std::string &name) {
    NSString *str = [NSString stringWithUTF8String: name.c_str()];
    NSString *path = [NSBundle.mainBundle pathForResource: str.stringByDeletingPathExtension ofType: str.pathExtension];
    if (path) {
        return path.UTF8String;
    } else {
        return ImportHandler::find_path(name);
    }
}
