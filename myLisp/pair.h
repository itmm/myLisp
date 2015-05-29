#if !defined(pair_h)
#define pair_h

    #include "element.h"
    
    class Pair: public Element {
        public:
            Pair(Element *car, Element *cdr): _car(car), _cdr(cdr) {}
            virtual ~Pair();
        
            Element *car() { return _car; }
            Element *cdr() { return _cdr; }
            
            static Pair *null();
            
            virtual Pair *as_pair();
        
        private:
            Element *_car;
            Element *_cdr;
    };

#endif
