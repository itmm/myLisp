#include "fnruntime.h"

#include <AppKit/AppKit.h>

#include "function_creator.h"

static SimpleFunctionCreator<FunctionRuntime> _creator("runtime");

static NSTimeInterval started = [NSDate timeIntervalSinceReferenceDate];

EPtr FunctionRuntime::apply(EPtr arguments, State &state) {
    unsigned long duration = static_cast<unsigned long>(([NSDate timeIntervalSinceReferenceDate] - started) * 1000);
    return state.creator()->new_number(BigInt(duration));
}
