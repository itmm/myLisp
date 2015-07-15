#include "rewriter.h"
#include "pair.h"
#include "dictionary.h"

Rewriter::~Rewriter() {}

Ptr Rewriter::rewrite(Ptr element, Creator &creator) {
	if (Element::as_dictionary(element)) { return rewrite_dictionary(element, creator); }
	if (Element::as_error(element)) { return rewrite_error(element, creator); }
	if (Element::as_function(element)) { return rewrite_function(element, creator); }
	if (Element::as_identifier(element)) { return rewrite_identifier(element, creator); }
	if (Element::as_number(element)) { return rewrite_number(element, creator); }
	if (Element::as_string(element)) { return rewrite_string(element, creator); }
	return rewrite_pair(element, creator);
}

Ptr Rewriter::rewrite_dictionary(Ptr dictionary, Creator &creator) {
	Dictionary *old_dict = dictionary->as_dictionary();
	bool was_modified = false;
	Dictionary *parent = old_dict->parent();
	if (parent) {
		Dictionary *new_parent = Element::as_dictionary(rewrite_dictionary(Ptr(parent, creator.collector()), creator));
		if (new_parent != parent) {
			parent = new_parent;
			was_modified = true;
		}
	}
	Ptr new_dict = creator.new_dictionary(parent);
	auto cur = old_dict->begin();
	auto end = old_dict->end();
	for (; cur != end; ++cur) {
		Ptr old_value = Ptr(cur->second, creator.collector());
		Ptr new_value = rewrite(old_value, creator);
		if (!was_modified && old_value != new_value) {
			was_modified = true;
		}
		new_dict->as_dictionary()->put(cur->first, new_value);
	}
	return was_modified ? new_dict : dictionary;
}

Ptr Rewriter::rewrite_error(Ptr error, Creator &creator) {
	return error;
}

Ptr Rewriter::rewrite_function(Ptr function, Creator &creator) {
	return function;
}

Ptr Rewriter::rewrite_identifier(Ptr identifier, Creator &creator) {
	return identifier;
}

Ptr Rewriter::rewrite_number(Ptr number, Creator &creator) {
	return number;
}

Ptr Rewriter::rewrite_pair(Ptr pair, Creator &creator) {
	if (pair) {
		Ptr new_car = rewrite(Ptr(Pair::car(pair), creator.collector()), creator);
		Ptr new_cdr = rewrite(Ptr(Pair::cdr(pair), creator.collector()), creator);
		if (Pair::car(pair) != new_car || Pair::cdr(pair) != new_cdr) {
			return creator.new_pair(new_car, new_cdr);
		}
	}
	return pair;
}

Ptr Rewriter::rewrite_string(Ptr str, Creator &creator) {
	return str;
}
