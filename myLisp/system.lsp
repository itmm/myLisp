;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this file defines basic functions ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; function definition shorthands ;;

(def "defn" (fn macro ("name" "args" "body") (def name (fn args body))))
(def "defm" (fn macro ("name" "args" "body") (def name (fn macro args body))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; assert can be used for unit-tests ;;

(def "tests-run" 0)
(def "tests-failed" 0)

(defn "assert" ("cnd" "msg") (do
    (def "tests-run" (+ 1 tests-run))
    (cond
        cnd true
        true (do
            (def "tests-failed" (+ 1 tests-failed))
            (err-print msg)
        )
    )
))

;;;;;;;;;;;;;;;;;
;; build lists ;;

(defn "cons" ("a" "b") (list a . b))

    (assert (= (cons 1 (2 3)) (1 2 3)) "cons not working")
    (assert (= (cons 1 ()) (1)) "can't cons empty")


;;;;;;;;;;;;;;;;;;;;;;;;
;; car/cdr shorthands ;;

(defn "caar" ("x") (car (car x)))

    (assert (= (caar ((1) 2)) 1) "caar not working")

(defn "cadr" ("x") (car (cdr x)))

    (assert (= (cadr (1 2 3)) 2) "cadr not working")

(defn "cdar" ("x") (cdr (car x)))

    (assert (= (cdar ((1 2) 3)) (2)) "cdar not working")

(defn "cddr" ("x") (cdr (cdr x)))

    (assert (= (cddr (1 2 3)) (3)) "cddr not working")

(defn "caaar" ("x") (car (car (car x))))
(defn "caadr" ("x") (car (car (cdr x))))
(defn "cadar" ("x") (car (cdr (car x))))
(defn "caddr" ("x") (car (cdr (cdr x))))
(defn "cdaar" ("x") (cdr (car (car x))))
(defn "cdadr" ("x") (cdr (car (cdr x))))
(defn "cddar" ("x") (cdr (cdr (car x))))
(defn "cdddr" ("x") (cdr (cdr (cdr x))))


;;;;;;;;;;;;;;;
;; increment ;;

(defn "1+" ("x") (+ 1 x))

    (assert (= (1+ 5) 6) "1+ not working")

(defm "if" ("cnd" "block" "else") (cond cnd block true else))

(defn "sum" ("n") (if (= n) 0 (+ n (sum (- n 1)))))

(defn "null?" ("lst") (= (list) lst))

    (assert (= (null? ()) true) "empty list is not null")
    (assert (= (null? (1)) false) "non-empty list is null")


;;;;;;;;;;;;;;;;;;;;;;;
;; contatenate lists ;;

(defn "flatten" "lsts" (do
    (defn "flatten-2" ("cur" "rest") (cond
        (null? cur) (apply flatten rest)
        (pair? cur) (cons (car cur) (flatten-2 (cdr cur) rest))
        true (cons cur (apply flatten rest))
    ))
    (cond
        (null? lsts) (list)
        (null? (car lsts)) (apply flatten (cdr lsts))
        true (flatten-2 (car lsts) (cdr lsts))
    )
))

    (assert (= (flatten) (list)) "can't flatten empty")
    (assert (= (flatten 1 2) (1 2)) "can't flatten numbers")
    (assert (= (flatten (1 2) (3)) (1 2 3)) "can't flatten lists")

(defm "or" ("a" "b") (if a a b))

    (assert (or 1 (err-print "or is not short-circuing")))

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

;; doubles is a helper method for ><

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

(assert (= (if true 3 4) 3) "if true not working")
(assert (= (if false 3 4) 4) "if false not working")
(assert (<= 2 2) "not 2 <= 2")
(assert (<= 2 3) "not 2 <= 3")
(assert (= (<= 3 2) false) "3 <= 2")
(assert (= (sort 8 3 5 7 2) (2 3 5 7 8)) "sort not working")

;;;;;;;;;;;;;;;;;;;;;;;;
;; unit-tests summary ;;

(if (= 0 tests-failed)
    (print tests-run " unit-tests passed")
    (err-print tests-failed " from " tests-run " unit-tests failed")
)