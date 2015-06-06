#include "t_helper.h"
#include "t_test.h"

#include <cassert>

#include "string.h"

static void test_1() { assert(String("8").as_number() == nullptr);; }
static void test_2() { assert(String("(1 2)").as_pair() == nullptr);; }
static void test_3() { assert(String("9").as_string() != nullptr);; }
static void test_4() { assert(String("pv").as_string()->str() == "pv");; }
static void test_5() { assert(String("abc").str() == "abc");; }
static void test_6() { OutSink OUT; assert((OUT << String("x y")) == "\"x y\"");; }
static void test_7() { OutSink OUT; assert((OUT << String("")) == "\"\"");; }
class TestInitstringHeader { public: TestInitstringHeader(); };
static TestInitstringHeader testInitstringHeader;
TestInitstringHeader::TestInitstringHeader() {
  all_tests().push_back(test_1);
  all_tests().push_back(test_2);
  all_tests().push_back(test_3);
  all_tests().push_back(test_4);
  all_tests().push_back(test_5);
  all_tests().push_back(test_6);
  all_tests().push_back(test_7);
};
