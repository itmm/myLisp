#if !defined(dictionary_h)
#define dictionary_h

    #include "element.h"

    #include <map>
    #include <string>

    class Dictionary: public Element {
        public:
            virtual ~Dictionary();
            virtual void free();
        
            void free_children();
        
            Dictionary *parent() { return _parent; }
        
            Element *get(const std::string &key);
            Dictionary *put(const std::string &key, Element *value);
        
            virtual Dictionary *as_dictionary();
            virtual void to_stream(std::ostream &stream) const;
        
        private:
            Dictionary(Dictionary *parent): _parent(parent) {}
        
            friend class Collector;
        
            Dictionary *_parent;
            std::map<std::string, Element *> _map;
    };

    /*TESTS:
     *
     *> #include "collector.h"
     *
     *  Collector().new_dictionary()->as_function() == nullptr
     *  Collector().new_dictionary()->as_dictionary() != nullptr
     *  Collector().new_dictionary()->as_number() == nullptr
     *  Collector().new_dictionary()->as_pair() == nullptr
     *  Collector().new_dictionary()->as_string() == nullptr
     *
     *  Collector().new_dictionary()->parent() == nullptr
     *  Collector().new_dictionary()->get("ab") == nullptr
     *
     */

#endif
