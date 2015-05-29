#include <iostream>

#include "collector.h"
#include "pair.h"

int main(int argc, const char * argv[]) {
    Collector collector;
    Pair *a = collector.new_pair(Pair::null(), Pair::null());
    Pair *b = collector.new_pair(a, Pair::null());
    collector.release_root(a);
    collector.collect();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    collector.release_root(b);
    collector.collect();
    
    return 0;
}
