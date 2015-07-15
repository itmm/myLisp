;; this file defines basic functions

(def "defn" (fn macro ("name" "args" "body") (def name (fn args body))))
(def "defm" (fn macro ("name" "args" "body") (def name (fn macro args body))))

(defn "cons" ("a" "b") (list a . b))
(defn "caar" ("x") (car (car x)))
(defn "cadr" ("x") (car (cdr x)))
(defn "cdar" ("x") (cdr (car x)))
(defn "cddr" ("x") (cdr (cdr x)))
(defn "caaar" ("x") (car (car (car x))))
(defn "caadr" ("x") (car (car (cdr x))))
(defn "cadar" ("x") (car (cdr (car x))))
(defn "caddr" ("x") (car (cdr (cdr x))))
(defn "cdaar" ("x") (cdr (car (car x))))
(defn "cdadr" ("x") (cdr (car (cdr x))))
(defn "cddar" ("x") (cdr (cdr (car x))))
(defn "cdddr" ("x") (cdr (cdr (cdr x))))

(defn "1+" ("x") (+ 1 x))

(defm "if" ("cnd" "block" "else") (cond cnd block true else))

(defn "sum" ("n") (if (= n) 0 (+ n (sum (- n 1)))))
(defn "assert" ("cnd" "msg") (cond cnd true true (err-print msg)))

(defn "cat-3" ("a" "b" "c") (cond
    (< (list) a) (cons (car a) (cat-3 (cdr a) b c))
    (< (list) b) (cons (car b) (cat-3 a (cdr b) c))
    (< (list) c) (cons (car c) (cat-3 a b (cdr c)))
    true (list)
))
(defn "or" ("a" "b") (if a a b))
(defn "filter" ("lst" "ref" "op") (cond
    (= (list) lst) (list)
    (op (car lst) ref) (cons (car lst) (filter (cdr lst) ref op))
    true (filter (cdr lst) ref op)
))
(defn "<=" ("a" "b") (or (= a b) (< a b)))
(defn ">" ("a" "b") (< b a))
(defn "sort" "a" (cond
    (= (list) a) a
    (= (list) (cdr a)) a
    true (cat-3
        (apply sort (filter (cdr a) (car a) <=))
        (list (car a))
        (apply sort (filter (cdr a) (car a) >))
    )
))
(defn "not" ("a") (cond a false true true))
(defn "doubles" ("a") (cond
    (= (list) a) false
    (= (list) (cdr a)) false
    (= (car a) (cadr a)) true
    true (doubles (cdr a))
))
(defn "><" "a" (not (doubles (apply sort a))))
(print "running unit tests")

(assert (= (cons 1 (list 2 3)) (list 1 2 3)) "cons not working")

(assert (= (if true 3 4) 3) "if true not working")
(assert (= (if false 3 4) 4) "if false not working")
(assert (<= 2 2) "not 2 <= 2")
(assert (<= 2 3) "not 2 <= 3")
(assert (= (<= 3 2) false) "3 <= 2")
(assert (= (cat-3 (2 3) (4) (5 6)) (2 3 4 5 6)))
(err-print "after cat-3")
(assert (= (sort 8 3 5 7 2) (2 3 5 7 8)) "sort not working")

(print "done with unit tests")
