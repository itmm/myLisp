#if ! defined(fndictionaryq_h)
#define fndictionaryq_h

#include "decider.h"

class FunctionDictionaryQuery : public Decider {
protected:
	virtual bool is_valid(Element *element) override;
};

#endif
