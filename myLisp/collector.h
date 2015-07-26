#ifndef collector_h
#define collector_h

    #include <algorithm>
    #include <vector>
    #include <set>

    class Dictionary;
    class Element;

    class Collector {
        public:
            Collector() {}
            ~Collector();

			Element *add_to_collector(Element *elm);

            bool remove_initial_lock(Element *elm);
            bool add_root(Element *root);
            bool remove_root(Element *root);

            void collect();

			class Visitor {
				public:
					Visitor(std::vector<Element *> &to_visit, std::set<Element *> &seen);
					void add_to_visit(Element *elm);

				private:
					std::vector<Element *> &_to_visit;
					std::set<Element *> &_seen;
			};

        private:
            Collector(const Collector &) = delete;
            Collector &operator=(const Collector &) = delete;

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

#endif
