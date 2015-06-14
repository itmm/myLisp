#if !defined(creator_h)
#define creator_h

	#include "ptr.h"
#include "fractional.h"

class Dictionary;

	class Creator {
		public:
			Creator(): _collector(new Collector()), _local_collector(true) {}
			Creator(Collector *collector): _collector(collector), _local_collector(false) {}
			~Creator() { if (_local_collector) delete _collector; }

			Collector *collector() { return _collector; }

			Ptr new_dictionary(Dictionary *parent = nullptr);
			Ptr new_number(const Fractional &value);
			Ptr new_pair(Element *car, Element *cdr);
			Ptr new_string(const std::string &value);

			Ptr eval(Ptr expression);

		private:
			Creator(const Creator &) = delete;
			Creator &operator=(const Creator &) = delete;

			Collector *_collector;
			bool _local_collector;
	};

	/*TESTS:
	 *
	 *	CONS(Pair::null(), Pair::null()) != Ptr()
	 *	CONS(Pair::null(), Pair::null()) != Ptr(Pair::null(), creator.collector())
	 *
	 */

#endif
