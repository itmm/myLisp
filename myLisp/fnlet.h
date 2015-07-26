#if ! defined(fnlet_h)
#define fnlet_h

    #include "function.h"

    class FunctionLet : public Function {
        public:
            virtual Ptr apply(Ptr arguments, State &state) override;
    };

#endif
