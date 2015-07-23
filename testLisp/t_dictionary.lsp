#include "t_test.h"
#include "parser.h"

#include <cassert>

#include "dictionary.h"

((fn ()  (assert (= (function? (dict)) false) "function? dict")))
((fn ()  (assert (= (dictionary? (dict)) true) "dictionary? dict")))
((fn ()  (assert (= (error? (dict)) false) "error? dict")))
((fn ()  (assert (= (number? (dict)) false) "number? dict")))
((fn ()  (assert (= (pair? (dict)) false) "pair? dict")))
((fn ()  (assert (= (string? (dict)) false) "string? dict")))
