#include "rewriter.h"
#include "pair.h"
#include "dictionary.h"

Rewriter::~Rewriter() {}

EPtr Rewriter::rewrite(EPtr element, Creator &creator) {
	if (Element::as_dictionary(element)) { return rewrite_dictionary(element, creator); }
	if (Element::as_error(element)) { return rewrite_error(element, creator); }
	if (Element::as_function(element)) { return rewrite_function(element, creator); }
	if (Element::as_identifier(element)) { return rewrite_identifier(element, creator); }
	if (Element::as_number(element)) { return rewrite_number(element, creator); }
	if (Element::as_string(element)) { return rewrite_string(element, creator); }
	return rewrite_pair(element, creator);
}

EPtr Rewriter::rewrite_dictionary(EPtr dictionary, Creator &creator) {
	Dictionary *old_dict = dictionary->as_dictionary();
	bool was_modified = false;
	Dictionary *parent = old_dict->parent();
	if (parent) {
		Dictionary *new_parent = Element::as_dictionary(rewrite_dictionary(EPtr(parent, creator.collector()), creator));
		if (new_parent != parent) {
			parent = new_parent;
			was_modified = true;
		}
	}
	EPtr new_dict = creator.new_dictionary(parent);
	auto cur = old_dict->begin();
	auto end = old_dict->end();
	for (; cur != end; ++cur) {
		EPtr old_value = EPtr(cur->second, creator.collector());
		EPtr new_value = rewrite(old_value, creator);
		if (!was_modified && old_value != new_value) {
			was_modified = true;
		}
		new_dict->as_dictionary()->put(cur->first, new_value);
	}
	return was_modified ? new_dict : dictionary;
}

EPtr Rewriter::rewrite_error(EPtr error, Creator &creator) {
	return error;
}

EPtr Rewriter::rewrite_function(EPtr function, Creator &creator) {
	return function;
}

EPtr Rewriter::rewrite_identifier(EPtr identifier, Creator &creator) {
	return identifier;
}

EPtr Rewriter::rewrite_number(EPtr number, Creator &creator) {
	return number;
}

EPtr Rewriter::rewrite_pair(EPtr pair, Creator &creator) {
	if (pair) {
		EPtr new_car = rewrite(EPtr(Pair::car(pair), creator.collector()), creator);
		EPtr new_cdr = rewrite(EPtr(Pair::cdr(pair), creator.collector()), creator);
		if (Pair::car(pair) != new_car || Pair::cdr(pair) != new_cdr) {
			return creator.new_pair(new_car, new_cdr);
		}
	}
	return pair;
}

EPtr Rewriter::rewrite_string(EPtr str, Creator &creator) {
	return str;
}
