#ifndef collector_h
#define collector_h

    #include <algorithm>
    #include <vector>

    class Pair;
    class Element;

    class Collector {
        public:
            Collector() {}
        
            Pair *new_pair(Element *car, Element *cdr);
            void add_root(Pair *root) { _roots.push_back(root); }
            void release_root(Pair *root) { _roots.erase(std::find(_roots.begin(), _roots.end(), root)); }
            void collect();
        
        private:
            Collector(const Collector &);
            Collector &operator=(const Collector &);
        
            std::vector<Pair *> _managed;
            std::vector<Pair *> _roots;
    };

#endif
