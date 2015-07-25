#include "t_test.h"
#include "parser.h"

#include <cassert>

#include "fndynamic.h"

((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (f 2 3) 5) "f 2 3")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (g 2 3) 5) "g 2 3")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (f) (error "too few arguments")) "f")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (g) 0) "g")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (f 2) (error "too few arguments")) "f 2")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (g 2) 2) "g 2")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (f 2 3 4) (error "too many arguments")) "f 2 3 4")))
((fn () (defn ("f" "a" "b") (+ a b))(defn ("g" . "args") (apply + args)) (assert (= (g 2 3 4) 9) "g 2 3 4")))
((fn () (defn ("f" "a" . "b") (+ a (apply + b))) (assert (= (f 2 3 4) 9) "mixed with 2 3 4")))
((fn () (defn ("f" "a" . "b") (+ a (apply + b))) (assert (= (f 2) 2) "mixed with 2")))
