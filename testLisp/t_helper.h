#ifndef t_helper_h
#define t_helper_h

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
                return _out.str() == expected;
            }
    };

#endif
