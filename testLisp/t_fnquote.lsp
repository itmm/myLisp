#include "t_test.h"
#include "parser.h"

#include <cassert>

#include "fnquote.h"

((fn ()  (assert (identifier? (quote +)) "quote +")))
