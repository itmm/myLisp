#include <iostream>

#include "collector.h"
#include "pair.h"
#include "string.h"

int main(int argc, const char * argv[]) {
    Collector collector;
    Pair *a = collector.new_pair(Pair::null(), Pair::null());
    Pair *b = collector.new_pair(Pair::null(), a);
    Pair *c = collector.new_pair(new String("abc"), b);
    collector.release_root(b);
    collector.release_root(a);
    collector.collect();
    
    // insert code here...
    std::cout << "This is myLisp\n";
    std::cout << *c << "\n";
    
    collector.release_root(c);
    collector.collect();
    
    return 0;
}
