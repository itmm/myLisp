#if !defined(state_h)
#define state_h

	#include "collector.h"
	#include "dictionary.h"
#include "creator.h"
#include "root_factory.h"

class State {
		public:
			State():
                _creator(new Creator()),
                _local_creator(true),
                _root(RootFactory(_creator).root()),
                _inserter(_root)
            {}
    
			State(Creator *creator, EPtr root):
                _creator(creator),
                _local_creator(false),
                _root(root),
                _inserter(_root)
            {}
    
            State(Creator *creator, EPtr root, EPtr inserter):
                _creator(creator),
                _local_creator(false),
                _root(root),
                _inserter(inserter)
            {}
            
			State(State &parent);
			~State() { _root = EPtr(); _inserter = EPtr(); if (_local_creator) delete _creator; }

			Creator *creator() { return _creator; }
			Collector *collector() { return _creator->collector(); }
			EPtr root() { return _root; }
			EPtr inserter() { return _inserter; }

			EPtr eval(EPtr expression);
			EPtr trueNumber() { return EPtr(_root->as_dictionary()->get("true"), collector()); }
			EPtr falseNumber() { return EPtr(_root->as_dictionary()->get("false"), collector()); }
			EPtr boolNumber(bool value) { return value ? trueNumber() : falseNumber(); }

			void setName(const std::string &name) { _name = name; }
			const std::string &name() const { return _name; }

			EPtr ptr(Element *element) { return EPtr(element, collector()); }
			EPtr error(const std::string &message) { return creator()->new_error(creator()->new_string(message), nullptr); }

		private:
			std::string _name;
			Creator *_creator;
			bool _local_creator;

			EPtr _root;
			EPtr _inserter;

			State &operator=(const State &) = delete;
	};

	inline State::State(State &parent):
		_creator(parent.creator()), _local_creator(false),
		_root(_creator->new_dictionary(Element::as_dictionary(parent.root()))),
		_inserter(parent.inserter())
	{
	}

#endif
