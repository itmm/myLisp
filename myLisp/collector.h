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

			void add_to_collector(Element *elm);

            bool remove_initial_lock(Element *elm);
            bool add_root(Element *root);
            bool remove_root(Element *root);

            void collect();
        
        private:
            Collector(const Collector &) = delete;
            Collector &operator=(const Collector &) = delete;

            void may_push_back(std::vector<Element *> &col, std::set<Element *> seen, Element *elm);
        
            std::vector<Element *> _managed;
            std::vector<Element *> _initial_locks;
            std::vector<Element *> _roots;
    };

    inline bool Collector::remove_initial_lock(Element *elm) {
		if (!elm) { return false; }
        auto i = std::find(_initial_locks.begin(), _initial_locks.end(), elm);
        if (i != _initial_locks.end()) {
            _initial_locks.erase(i);
            return true;
        }
        return false;
    }

    inline bool Collector::add_root(Element *root) {
        if (root && root != Pair::null()) {
            _roots.push_back(root);
			remove_initial_lock(root);
            return true;
        }
        return false;
    }

    inline bool Collector::remove_root(Element *root) {
		if (!root) { return false; }
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
     *  Collector().remove_initial_lock(nullptr) == false
     *  Collector().add_root(nullptr) == false
     *  Collector().remove_root(nullptr) == false
     */

#endif
