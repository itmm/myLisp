#include "expander.h"

#include "dictionary.h"
#include "identifier.h"

Ptr Expander::rewrite_identifier(Ptr identifier, Creator &creator) {
	Dictionary *dict = _replacements->as_dictionary();
	if (dict->contains(identifier->as_identifier()->str())) {
		return Ptr(_replacements->as_dictionary()->get(identifier), creator.collector());
	}
	return identifier;
}
