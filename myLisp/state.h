#if !defined(state_h)
#define state_h

	#include "collector.h"
	#include "dictionary.h"
#include "creator.h"
#include "root_factory.h"

class State {
		public:
			State(): _creator(new Creator()), _local_creator(true), _root(RootFactory(_creator).root()), _inserter(_root) {}
			State(Creator *creator, Ptr root): _creator(creator), _local_creator(false), _root(root), _inserter(_root) {}
	State(Creator *creator, Ptr root, Ptr inserter): _creator(creator), _local_creator(false), _root(root), _inserter(inserter) {}
			State(State &parent);
			~State() { _root = Ptr(); _inserter = Ptr(); if (_local_creator) delete _creator; }

			Creator *creator() { return _creator; }
			Collector *collector() { return _creator->collector(); }
			Ptr root() { return _root; }
			Ptr inserter() { return _inserter; }

			Ptr eval(Ptr expression);
			Ptr trueNumber() { return Ptr(_root->as_dictionary()->get("true"), collector()); }
			Ptr falseNumber() { return Ptr(_root->as_dictionary()->get("false"), collector()); }
			Ptr boolNumber(bool value) { return value ? trueNumber() : falseNumber(); }

			void setName(const std::string &name) { _name = name; }
			const std::string &name() const { return _name; }

			Ptr ptr(Element *element) { return Ptr(element, collector()); }
			Ptr error(const std::string &message) { return creator()->new_error(message); }

		private:
			std::string _name;
			Creator *_creator;
			bool _local_creator;

			Ptr _root;
			Ptr _inserter;

			State &operator=(const State &) = delete;
	};

	inline State::State(State &parent):
		_creator(parent.creator()), _local_creator(false),
		_root(_creator->new_dictionary(Element::as_dictionary(parent.root()))),
		_inserter(parent.inserter())
	{
	}

#endif
