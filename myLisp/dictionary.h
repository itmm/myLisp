#if !defined(dictionary_h)
#define dictionary_h

    #include "element.h"

    #include <map>
    #include <string>

    class Dictionary: public Element {
		public:
			virtual void add_to_visit(Collector::Visitor &visitor) override;

            Dictionary *parent() { return _parent; }
        
            Element *get(const std::string &key);
            Dictionary *put(const std::string &key, Element *value);
        
            virtual Dictionary *as_dictionary();
            virtual void to_stream(std::ostream &stream) const;
        
        private:
            Dictionary(Dictionary *parent): _parent(parent) {}
        
            friend class Creator;
        
            Dictionary *_parent;
            std::map<std::string, Element *> _map;
	};

    /*TESTS:
     *
     *> #include "creator.h"
     *
     *  Creator().new_dictionary()->as_function() == nullptr
     *  Creator().new_dictionary()->as_dictionary() != nullptr
     *  Creator().new_dictionary()->as_number() == nullptr
     *  Creator().new_dictionary()->as_pair() == nullptr
     *  Creator().new_dictionary()->as_string() == nullptr
     *
     *  Creator().new_dictionary()->as_dictionary()->parent() == nullptr
     *  Creator().new_dictionary()->as_dictionary()->get("ab") == nullptr
     *
     */

#endif
