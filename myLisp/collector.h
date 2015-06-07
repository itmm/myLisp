#ifndef collector_h
#define collector_h

    #include <algorithm>
    #include <vector>
    #include <set>

    #include "pair.h"

    class Dictionary;
    class Element;

    class Collector {
        public:
            Collector() {}
            ~Collector();
            
            Pair *new_pair(Element *car, Element *cdr);
            Dictionary *new_dictionary(Dictionary *parent = nullptr);
            Dictionary *root_dictionary();
        
            bool release_initial_lock(Element *elm);
            bool make_root(Element *root);
            bool release_root(Element *root);

            void collect();
        
        private:
            Collector(const Collector &) = delete;
            Collector &operator=(const Collector &) = delete;

            void may_push_back(std::vector<Element *> &col, std::set<Element *> seen, Element *elm);
        
            std::vector<Element *> _managed;
            std::vector<Element *> _initial_locks;
            std::vector<Element *> _roots;
    };

    inline bool Collector::release_initial_lock(Element *elm) {
        auto i = std::find(_initial_locks.begin(), _initial_locks.end(), elm);
        if (i != _initial_locks.end()) {
            _initial_locks.erase(i);
            return true;
        }
        return false;
    }

    inline bool Collector::make_root(Element *root) {
        if (root && root->as_pair()) {
            _roots.push_back(root);
			release_initial_lock(root);
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
     *> #include "dictionary.h"
     *> #include "number.h"
     *
     *  Collector().release_initial_lock(nullptr) == false
     *  Collector().make_root(nullptr) == false
     *  Collector().release_root(nullptr) == false
     *
     *  Collector().root_dictionary()->get("Infinity")->as_number()->value() == Fractional::infinity()
     */

#endif
