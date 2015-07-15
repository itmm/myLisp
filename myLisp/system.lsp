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

(defn "null?" ("lst") (= (list) lst))

(defn "flatten" "lsts" (cond
    (null? lsts) (list)
    (null? (car lsts)) (apply flatten (cdr lsts))
    true (flatten-2 (car lsts) (cdr lsts))
))
(defn "flatten-2" ("cur" "rest") (cond
    (null? cur) (apply flatten rest)
    (pair? cur) (cons (car cur) (flatten-2 (cdr cur) rest))
    true (cons cur (apply flatten rest))
))

    (assert (= (flatten) (list)) "can't flatten empty")
    (assert (= (flatten 1 2) (1 2)) "can't flatten numbers")
    (assert (= (flatten (1 2) (3)) (1 2 3)) "can't flatten lists")

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
    true (flatten
        (apply sort (filter (cdr a) (car a) <=))
        (list (car a))
        (apply sort (filter (cdr a) (car a) >))
    )
))
(defn "not" ("a") (cond a false true true))

; doubles is a helper method for ><

(defn "doubles" ("a") (cond
    (= (list) a) false
    (= (list) (cdr a)) false
    (= (car a) (cadr a)) true
    true (doubles (cdr a))
))

    (assert (= (doubles (2 3 3 5)) true) "doubles not found")
    (assert (= (doubles (2 3 5)) false) "no doubles in 2 3 5")
    (assert (= (doubles) false) "no doubles in empty call")
    (assert (= (doubles (2)) false) "no doubles with one argument")

(defn "><" "a" (not (doubles (apply sort a))))

(assert (= (cons 1 (list 2 3)) (list 1 2 3)) "cons not working")

(assert (= (if true 3 4) 3) "if true not working")
(assert (= (if false 3 4) 4) "if false not working")
(assert (<= 2 2) "not 2 <= 2")
(assert (<= 2 3) "not 2 <= 3")
(assert (= (<= 3 2) false) "3 <= 2")
(assert (= (sort 8 3 5 7 2) (2 3 5 7 8)) "sort not working")
