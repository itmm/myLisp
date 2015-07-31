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

			EPtr new_element(Element *element);
			EPtr new_error(Element *head, Element *rest);
			EPtr new_dictionary(Dictionary *parent = nullptr);
			EPtr new_number(const Fractional &value);
			EPtr new_identifier(const std::string &value);
			EPtr new_pair(Element *car, Element *cdr);
			EPtr new_string(const std::string &value);

		private:
			Creator(const Creator &) = delete;
			Creator &operator=(const Creator &) = delete;

			Collector *_collector;
			bool _local_collector;
	};

#endif
