#if !defined(dictionary_h)
#define dictionary_h

    #include "element.h"

    #include <map>
    #include <string>

    class Dictionary: public Element {
		public:
			virtual void add_to_visit(Collector::Visitor &visitor) override;

            Dictionary *parent() { return _parent; }

        	bool contains(const std::string &key) const;
            Element *get(const std::string &key) const;
			Element *get(Element *key) const;
            Dictionary *put(const std::string &key, Element *value);

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
			bool is_subset_of(const Dictionary *other) const;

            virtual Dictionary *as_dictionary();
            virtual void to_stream(std::ostream &stream) const;

        	std::map<std::string, Element *>::const_iterator begin() const;
        	std::map<std::string, Element *>::const_iterator end() const;

        private:
            Dictionary(Dictionary *parent): _parent(parent) {}
        
            friend class Creator;
        
            Dictionary *_parent;
            std::map<std::string, Element *> _map;
	};

    /*C++-TESTS:
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
