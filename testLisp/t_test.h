#if !defined(t_test_h)
#define t_test_h

    #include <vector>

    typedef void (*Test)();

    std::vector<Test> &all_tests();

#endif
