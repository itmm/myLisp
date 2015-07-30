#if ! defined(function_pool_h)
#define function_pool_h

    #include <vector>

    class Creator;
    class Dictionary;
    class FunctionCreator;
    
    class FunctionPool {
        public:
            static void add_creator(FunctionCreator *creator);
            static void insert_functions(Dictionary *dict, Creator *creator);
        
        private:
            static std::vector<FunctionCreator *> &add(FunctionCreator *creator);
    };

#endif
