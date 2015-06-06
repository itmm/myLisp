#ifndef t_helper_h
#define t_helper_h

    #include <iostream>
    #include <sstream>

    class OutSink {
        private:
            std::ostringstream _out;
            OutSink(const OutSink &);
            OutSink &operator=(const OutSink &);
        
        public:
            OutSink() {}
        
            template<class T> OutSink &operator<<(const T &value) {
                _out << value;
                return *this;
            }
        
            bool operator==(const char *expected) const {
                if (_out.str() != expected) {
                    std::cout << "\"" << _out.str() << "\" != \"" << expected << "\"\n";
                    return false;
                }
                return true;
            }
    };

#endif
