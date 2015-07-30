#if ! defined(function_creator_h)
#define function_creator_h

    #include "function.h"
    #include "function_pool.h"

    #include <string>

    class FunctionCreator {
        public:
            FunctionCreator(const std::string &key): _key(key) { FunctionPool::add_creator(this); }
        
            const std::string key() const { return _key; }
            virtual Function *create() = 0;
        
        private:
            std::string _key;
    };

    template <class T> class SimpleFunctionCreator : public FunctionCreator {
        public:
            SimpleFunctionCreator(const std::string &key): FunctionCreator(key) {}
        
            virtual Function *create() override { return new T(); }
    };

#endif
