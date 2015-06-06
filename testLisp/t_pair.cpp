#include "t_helper.h"
#include "t_test.h"

#include <cassert>

#include "pair.h"

#include "String.h"

static void test_1() { assert(Pair::null()->as_pair() != nullptr);; }
static void test_2() { assert(Pair::null()->as_number() == nullptr);; }
static void test_3() { assert(Pair::null()->as_string() == nullptr);; }
static void test_4() { assert(Pair::null()->as_pair() == Pair::null());; }
static void test_5() { assert(Pair::null()->car() == Pair::null());; }
static void test_6() { assert(Pair::null()->cdr() == Pair::null());; }
static void test_7() { OutSink OUT; assert((OUT << Pair(new String("a"), new Pair(new String("b"), Pair::null()))) == "(\"a\" \"b\")");; }
static void test_8() { OutSink OUT; assert((OUT << *Pair::null()) == "()");; }
static void test_9() { OutSink OUT; assert((OUT << Pair(new String("a"), new String("b"))) == "(\"a\" . \"b\")");; }
class TestInitpairHeader { public: TestInitpairHeader(); };
static TestInitpairHeader testInitpairHeader;
TestInitpairHeader::TestInitpairHeader() {
  all_tests().push_back(test_1);
  all_tests().push_back(test_2);
  all_tests().push_back(test_3);
  all_tests().push_back(test_4);
  all_tests().push_back(test_5);
  all_tests().push_back(test_6);
  all_tests().push_back(test_7);
  all_tests().push_back(test_8);
  all_tests().push_back(test_9);
};
