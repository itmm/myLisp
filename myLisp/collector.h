#ifndef collector_h
#define collector_h

    #include <algorithm>
    #include <vector>

    #include "pair.h"

    class Element;

    class Collector {
        public:
            Collector() {}
        
            Pair *new_pair(Element *car, Element *cdr);
            bool release_initial_bondage(Element *elm);
            bool make_root(Element *root);
            bool release_root(Element *root);
            void collect();
        
        private:
            Collector(const Collector &);
            Collector &operator=(const Collector &);
        
            std::vector<Element *> _managed;
            std::vector<Element *> _initial_bondages;
            std::vector<Element *> _roots;
    };

    inline bool Collector::release_initial_bondage(Element *elm) {
        auto i = std::find(_initial_bondages.begin(), _initial_bondages.end(), elm);
        if (i != _initial_bondages.end()) {
            _initial_bondages.erase(i);
            return true;
        }
        return false;
    }

    inline bool Collector::make_root(Element *root) {
        if (root && root->as_pair()) {
            _roots.push_back(root);
            release_initial_bondage(root);
            return true;
        }
        return false;
    }

    inline bool Collector::release_root(Element *root) {
        auto i = std::find(_roots.begin(), _roots.end(), root);
        if (i != _roots.end()) {
            _roots.erase(i);
            return true;
        }
        return false;
    }

    /*TESTS:
     *
     *  Collector().release_initial_bondage(nullptr) == false
     *  Collector().make_root(nullptr) == false
     *  Collector().release_root(nullptr) == false
     *
     */

#endif
