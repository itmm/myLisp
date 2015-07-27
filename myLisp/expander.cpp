#include "expander.h"

#include "dictionary.h"
#include "identifier.h"

EPtr Expander::rewrite_identifier(EPtr identifier, Creator &creator) {
	Dictionary *dict = _replacements->as_dictionary();
	if (dict->contains(identifier->as_identifier()->str())) {
		return EPtr(_replacements->as_dictionary()->get(identifier), creator.collector());
	}
	return identifier;
}
