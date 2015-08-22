#if ! defined(fnruntime_h)
#define fnruntime_h

    #include "function.h"

    class FunctionRuntime : public Function {
        virtual EPtr apply(EPtr arguments, State &state) override;
    };
    
#endif
