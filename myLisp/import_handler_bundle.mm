#include "import_handler_bundle.h"

#import <Foundation/Foundation.h>

std::vector<std::string> ImportHandlerBundle::find_paths(const std::string &name) {
    NSString *str = [NSString stringWithUTF8String: name.c_str()];
    NSString *base = str.stringByDeletingPathExtension;
    NSString *ext = str.pathExtension;

    std::vector<std::string> result;
    
    NSRange range = [base rangeOfString: @"*"];
    if (range.length) {
        NSString *prefix = [base substringToIndex: range.location];
        NSString *suffix = [base substringFromIndex: range.location + range.length];
        
        NSArray *files = [NSBundle.mainBundle pathsForResourcesOfType:ext inDirectory:nil];
        for (NSUInteger i = 0, count = files.count; i < count; ++i) {
            NSString *path = files[i];
            NSString *b = path.lastPathComponent.stringByDeletingPathExtension;
            if (prefix.length && ! [b hasPrefix: prefix]) continue;
            if (suffix.length && ! [b hasSuffix: suffix]) continue;
            result.push_back(path.UTF8String);
        }
    } else {
        NSString *path = [NSBundle.mainBundle pathForResource: base ofType: ext];
        if (path) {
            result.push_back(path.UTF8String);
        }
    }
    
    if (result.size()) {
        return result;
    } else {
        return ImportHandler::find_paths(name);
    }
}
