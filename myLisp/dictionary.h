#if !defined(dictionary_h)
#define dictionary_h

    #include "element.h"

    #include <map>
    #include <string>

    class Dictionary : public Element {
		public:
			virtual void add_to_visit(Collector::Visitor &visitor) override;

            Dictionary *parent() { return _parent; }

        	bool contains(const std::string &key) const;
            Element *get(const std::string &key) const;
			Element *get(Element *key) const;
            Dictionary *put(const std::string &key, Element *value);
            Dictionary *add(const std::string &key, Element *value);

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
			bool is_subset_of(const Dictionary *other) const;
			virtual bool is_less(Element *other) const override;

            virtual Dictionary *as_dictionary();
            virtual void to_stream(std::ostream &stream, bool escape) const;

        	std::map<std::string, Element *>::const_iterator begin() const;
        	std::map<std::string, Element *>::const_iterator end() const;

        private:
            friend class Creator;

            Dictionary(Dictionary *parent): _parent(parent) {}

            Dictionary *_parent;
            std::map<std::string, Element *> _map;
	};

	/*TESTS:
	 *
	 *	(assert (= (function? (dict)) false))
	 *	(assert (= (dictionary? (dict)) true))
	 *	(assert (= (error? (dict)) false))
	 *	(assert (= (number? (dict)) false))
	 *	(assert (= (pair? (dict)) false))
	 *	(assert (= (string? (dict)) false))
     *
     *  (assert (= (< (dict) (dict)) false))
     *  (assert (= (< (dict ("a" 2)) (dict)) false))
     *  (assert (= (< (dict) (dict ("a" 2))) true))
     *  (assert (= (< (dict ("a" 2)) (dict ("b" 2))) true))
     *  (assert (= (< (dict ("a" 2)) (dict ("a" 2))) false))
     *  (assert (= (< (dict ("b" 2)) (dict ("a" 2))) false))
     *  (assert (= (< (dict ("a" 2)) (dict ("a" 3))) true))
     *  (assert (= (< (dict ("a" 2) ("b" 2)) (dict ("a" 2) ("b" 3))) true))
	 */
     
#endif
