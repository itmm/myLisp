#if !defined(root_factory_h)
#define root_factory_h

	#include "creator.h"

	class RootFactory {
		public:
			RootFactory(Creator *creator): _creator(creator), _local_creator(false) {}
			RootFactory(): _creator(new Creator()), _local_creator(true) {}
			~RootFactory() { if (_local_creator) delete _creator; }

			EPtr root();

		private:
			RootFactory(const RootFactory &) = delete;
			RootFactory &operator=(const RootFactory &) = delete;

			Creator *_creator;
			bool _local_creator;
	};

/*TESTS:
 *
 *	(assert (number? infinity))
 *	(assert (number? not-a-number))
 *	(assert (function? +))
 *	(assert (function? def))
 *	(assert (number? true))
 *	(assert (number? false))
 *	(assert (function? list))
 *	(assert (function? fn))
 *	(assert (function? car))
 *	(assert (function? cond))
 *	(assert (function? cdr))
 *	(assert (function? =))
 *	(assert (function? quote))
 *	(assert (function? import))
 *	(assert (function? error))
 *	(assert (function? *))
 *	(assert (function? print))
 *	(assert (function? err-print))
 *	(assert (function? true?))
 *	(assert (function? false?))
 *	(assert (function? str-print))
 *  (assert (function? _str-length))
 *	(assert (function? pair?))
 *	(assert (function? string?))
 *	(assert (function? number?))
 *	(assert (function? function?))
 *	(assert (function? error?))
 *	(assert (function? identifier?))
 *	(assert (function? dictionary?))
 *	(assert (function? <))
 *	(assert (function? and))
 *	(assert (function? dict))
 *	(assert (function? expand))
 *	(assert (function? apply))
 *	(assert (function? /))
 *	(assert (function? numerator))
 *	(assert (function? denominator))
 *	(assert (function? remainder))
 *	(assert (function? gcd))
 *  (assert (function? let))
 *  (assert (function? random))
 *  (assert (function? round))
 *  (assert (function? numeric))
 *  (assert (function? runtime))
 */

#endif
