#if !defined(state_h)
#define state_h

	#include "collector.h"
	#include "dictionary.h"

	class State {
		public:
			State(): _collector(new Collector()) {}
			~State() {
				delete _collector;
			}

			Collector &collector() { return *_collector; }
			Dictionary *root() { return _root; }

		private:
			Collector *_collector;
			Dictionary *_root;

			State(const State &) = delete;
			State &operator=(const State &) = delete;
	};

#endif
