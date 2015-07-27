#if ! defined(fnlet_h)
#define fnlet_h

    #include "function.h"

    class FunctionLet : public Function {
        public:
            virtual EPtr apply(EPtr arguments, State &state) override;
    };

#endif
