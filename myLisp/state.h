#if !defined(state_h)
#define state_h

	#include "collector.h"
	#include "dictionary.h"
#include "creator.h"
#include "root_factory.h"

class State {
		public:
			State(): _creator(new Creator()), _local_creator(true), _root(RootFactory(_creator).root()) {}
			State(Creator *creator, Ptr root): _creator(creator), _local_creator(false), _root(root) {}
			State(State &parent);
			~State() { _root = Ptr(); if (_local_creator) delete _creator; }

			Creator *creator() { return _creator; }
			Collector *collector() { return _creator->collector(); }
			Ptr root() { return _root; }

			Ptr eval(Ptr expression);

		private:
			Creator *_creator;
			bool _local_creator;

			Ptr _root;

			State &operator=(const State &) = delete;
	};

	inline State::State(State &parent):
		_creator(parent.creator()), _local_creator(false),
		_root(_creator->new_dictionary(Element::as_dictionary(parent.root())))
	{
	}

#endif
