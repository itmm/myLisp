#if !defined(fnimport_h)
#define fnimport_h

	#include "function.h"
    #include "import_handler.h"

	class FunctionImport : public Function {
		public:
            FunctionImport(): _handler(new ImportHandler()) {}
            virtual ~FunctionImport();

			virtual EPtr apply_evaled(EPtr arguments, State &state) override;
        
            void setHandler(ImportHandler *handler);
        
            EPtr import(const std::string &name, State &state);
        
        private:
            ImportHandler *_handler;
	};

	/*TESTS:
	 *
	 *+	(= (import "simple.lsp") true)
	 *
	 *	(assert (= answer 42))
	 */

	/*TESTS:
	 *
	 *	(assert (= (import 42) (error "string expected")))
	 *	(assert (= (import "non-existent.lsp") (error "can't import" "non-existent.lsp")))
	 */

#endif
