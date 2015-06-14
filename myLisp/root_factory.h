#if !defined(root_factory_h)
#define root_factory_h

	#include "creator.h"

	class RootFactory {
		public:
			RootFactory(Creator *creator): _creator(creator), _local_creator(false) {}
			RootFactory(): _creator(new Creator()), _local_creator(true) {}
			~RootFactory() { if (_local_creator) delete _creator; }

			Ptr root();

		private:
			RootFactory(const RootFactory &) = delete;
			RootFactory &operator=(const RootFactory &) = delete;

			Creator *_creator;
			bool _local_creator;
	};

/*TESTS:
 *
 *>	#include "dictionary.h"
 *> #include "number.h"
 *
 *	RootFactory().root()->as_dictionary()->get("Infinity")->as_number()->value() == Fractional::infinity()
 *
 */
#endif
