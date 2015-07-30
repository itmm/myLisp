#include "function_pool.h"

#include "creator.h"
#include "dictionary.h"
#include "function_creator.h"

std::vector<FunctionCreator *> &FunctionPool::add(FunctionCreator *creator) {
    static std::vector<FunctionCreator *> creators;
    if (creator) creators.push_back(creator);
    return creators;
}

void FunctionPool::add_creator(FunctionCreator *creator) {
    add(creator);
}

void FunctionPool::insert_functions(Dictionary *dict, Creator *creator) {
    auto &v = add(nullptr);
    auto cur = v.begin();
    auto end = v.end();
    
    for (; cur != end; ++cur) {
        dict->put((**cur).key(), creator->new_element((**cur).create()));
    }
}
