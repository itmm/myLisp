#if ! defined(fnprint_h)
#define fnprint_h

	#include "function.h"
    #include "stream_handler.h"

	class FunctionPrint : public Function {
		public:
			FunctionPrint(StreamHandler *handler): _handler(handler) {}
            virtual ~FunctionPrint();
        
            void setHandler(StreamHandler *handler);
            
			virtual EPtr apply_evaled(EPtr arguments, State &state) override;

		private:
			StreamHandler *_handler;
	};

	/*TESTS:
	 *
	 *	(assert (= (str-print) ""))
	 *	(assert (= (str-print false) "false"))
	 *	(assert (= (str-print 1 2 3) "123"))
	 *	(assert (= (str-print "1" "2" "3") "123"))
	 *	(assert (= (str-print unused-identifier) "unused-identifier"))
	 */

#endif