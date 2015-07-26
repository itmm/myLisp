;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this file defines basic functions ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; function definition shorthands ;;

(def "defn" (fn macro ("args" . "body") (def (car args) (fn (cdr args) . body))))
(def "defm" (fn macro ("args" . "body") (def (car args) (fn macro (cdr args) . body))))

;;;;;;;;;;;;;;;
;; constants ;;

(def "infinity" 1/0)
(def "not-a-number" 0/0)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; assert can be used for unit-tests ;;

(def "tests-run" 0)
(def "tests-failed" 0)

(defn ("assert-setup")
    (def "tests-run" 0)
    (def "tests-failed" 0)
)

(def "else" true)

(defn ("assert" "cnd" "msg")
    (def "tests-run" (+ 1 tests-run))
    (cond
        (cnd true)
        (else
            (def "tests-failed" (+ 1 tests-failed))
            (err-print msg "not working")
        )
    )
)

;;;;;;;;;;;;;;;;;
;; build lists ;;

(defn ("cons" "a" "b") (list a . b))

    (assert (= (cons 1 (2 3)) (1 2 3)) "cons")
    (assert (= (cons 1 ()) (1)) "empty cons")

;;;;;;;;;;;;;;;;;;;;;;;;
;; car/cdr shorthands ;;

(defn ("caar" "x") (car (car x)))

    (assert (= (caar ((1) 2)) 1) "caar")

(defn ("cadr" "x") (car (cdr x)))

    (assert (= (cadr (1 2 3)) 2) "cadr")

(defn ("cdar" "x") (cdr (car x)))

    (assert (= (cdar ((1 2) 3)) (2)) "cdar")

(defn ("cddr" "x") (cdr (cdr x)))

    (assert (= (cddr (1 2 3)) (3)) "cddr")

(defn ("caaar" "x") (car (car (car x))))
(defn ("caadr" "x") (car (car (cdr x))))
(defn ("cadar" "x") (car (cdr (car x))))
(defn ("caddr" "x") (car (cdr (cdr x))))
(defn ("cdaar" "x") (cdr (car (car x))))
(defn ("cdadr" "x") (cdr (car (cdr x))))
(defn ("cddar" "x") (cdr (cdr (car x))))
(defn ("cdddr" "x") (cdr (cdr (cdr x))))


;;;;;;;;;;;;;;;
;; increment ;;

(defn ("1+" "x") (+ 1 x))

    (assert (= (1+ 5) 6) "1+")

(defm ("if" "condition" "true-block" "false-block") (cond (condition true-block) (else false-block)))

    (assert (= (if true 3 4) 3) "if true")
    (assert (= (if false 3 4) 4) "if false")

(defn ("sum" "n") (if (= n) 0 (+ n (sum (- n 1)))))

(defn ("null?" "lst") (= () lst))

    (assert (= (null? ()) true) "empty null?")
    (assert (= (null? (1)) false) "non-empty null?")
    (assert (= (null? 0) false) "null? 0")
    (assert (= (null? "()") false) "null? \"()\"")

(defm ("apply" "f" "args") (f . args))

    (assert (= (apply + (2 3 4)) 9) "apply")

;;;;;;;;;;;;;;;;;;;;;;;
;; contatenate lists ;;

(defn ("flatten" . "lsts")
    (defn ("flatten-2" "cur" "rest") (cond
        ((null? cur) (apply flatten rest))
        ((pair? cur) (cons (car cur) (flatten-2 (cdr cur) rest)))
        (else (cons cur (apply flatten rest)))
    ))
    (cond
        ((null? lsts) (list))
        ((null? (car lsts)) (apply flatten (cdr lsts)))
        (else (flatten-2 (car lsts) (cdr lsts)))
    )
)

    (assert (= (flatten) (list)) "empty flatten")
    (assert (= (flatten 1 2) (1 2)) "flatten numbers")
    (assert (= (flatten (1 2) (3)) (1 2 3)) "flatten lists")


;;;;;;;;;;
;; bool ;;

(defm ("and" "a" "b" . "args") (if a
    (if (null? args)
        b
        (and b . args)
    )
    a
))

    (assert (= (and false false) false) "and false false")
    (assert (= (and false true) false) "and false true")
    (assert (= (and true false) false) "and true false")
    (assert (= (and true 1) true) "and true 1")

    (assert (= (and 1 2 3 4) 4) "and 1 2 3 4")

(defm ("or" "a" "b" . "args") (if a
    a
    (if (null? args)
        b
        (or b . args)
    )
))

    (assert (= (or 1 (err-print "or is not short-circuing")) 1) "or")
    (assert (= (or 0 false 2) 2) "or 0 false 2")
    (assert (= (or false 0) 0) "or false 0")

(defn ("not" "a") (false? a))

    (assert (= (not 1) false) "not true")
    (assert (= (not 0) true) "not false")

(defn ("xor" "a" "b" . "args") (if a
    (if (null? args) (not b) (not (xor b . args)))
    (if (null? args) (true? b) (xor b . args))
))

    (assert (= (xor 0 0) false) "xor 0 0")
    (assert (= (xor 0 1) true) "xor 0 1")
    (assert (= (xor 1 0) true) "xor 1 0")
    (assert (= (xor 1 1) false) "xor 1 1")

    (assert (= (xor 0 1 0) true) "xor 0 1 0")


;;;;;;;;;;;;;;;;;;;;;;;
;; filter & listable ;;

(defn ("filter" "lst" "ref" "op") (cond
    ((= (list) lst) (list))
    ((op (car lst) ref) (cons (car lst) (filter (cdr lst) ref op)))
    (else (filter (cdr lst) ref op))
))

    (assert (= (filter (1 2 3 4) 3 <) (1 2)) "filter")
    (assert (= (filter (4 3 2 1) 3 <) (2 1)) "reverse filter")

(defm ("listable" "cnd" "a" "b" . "args") (let (("b-evaled" b) ("cnd-evaled" cnd))
    (if (cnd-evaled a b-evaled)
        (if (null? args)
            true
            (listable cnd-evaled b . args)
        )
        false
    )
))

;;;;;;;;;;;;;;;;;;;;;;;;;;
;; comparison shortcuts ;;

(defm ("<=" . "args") (listable (fn ("a" "b") (or (= a b) (< a b))) . args))

    (assert (= (<= 2 2) true) "2 <= 2")
    (assert (= (<= 2 3) true) "2 <= 3")
    (assert (= (<= 3 2) false) "3 <= 2")
    (assert (= (<= 1 2 2 3) true) "<= 1 2 2 3")
    (assert (= (<= 1 2 1) false) "<= 1 2 1")
    (assert (= (<= 2 1 (err-print "<= lazy not working")) false) "<= 2 1 err")

(defm (">" . "args") (listable (fn ("a" "b") (< b a)) . args))

    (assert (= (> 5 4 3) true) "> 5 4 3")
    (assert (= (> 5 4 5) false) "> 5 4 5")

(defm (">=" . "args") (listable (fn ("a" "b") (or (= a b) (< b a))) . args))

    (assert (= (>= 5 4 4) true) ">= 5 4 4")
    (assert (= (>= 5 4 5) false) ">= 5 4 5")

(defn ("sort" . "a") (cond
    ((= (list) a) a)
    ((= (list) (cdr a)) a)
    (else (flatten
        (apply sort (filter (cdr a) (car a) <=))
        (list (car a))
        (apply sort (filter (cdr a) (car a) >))
    ))
))

    (assert (= (sort 8 3 5 7 2) (2 3 5 7 8)) "sort")

;; doubles is a helper method for ><

(defn ("doubles" "a") (cond
    ((= (list) a) false)
    ((= (list) (cdr a)) false)
    ((= (car a) (cadr a)) true)
    (else (doubles (cdr a)))
))

    (assert (= (doubles (2 3 3 5)) true) "doubles in 2 3 3 5")
    (assert (= (doubles (2 3 5)) false) "no in 2 3 5")
    (assert (= (doubles ()) false) "empty doubles")
    (assert (= (doubles (2)) false) "single doubles")

(defn ("><" . "a") (not (doubles (apply sort a))))

    (assert (= (>< 1 2 3) true) "not equal")
    (assert (= (><) true) "empty not equal")
    (assert (= (><) 1) "single not equal")
    (assert (= (>< 2 1 2) false) "double not equal")


;;;;;;;;
;; do ;;

(defm ("do" . "statements") (cond (true . statements)))

    (assert (= (do (+ 1 2) (+ 2 3)) 5) "do")


;;;;;;;;;;
;; sign ;;

(defn ("sign" "a") (cond
    ((= a 0) 0)
    ((< a 0) -1)
    (else 1)
))

    (assert (= (sign 5) 1) "sign 5")
    (assert (= (sign 0) 0) "sign 0")
    (assert (= (sign -3) -1) "sign -3")

(import "tests.lsp")
(import "sicp-tests.lsp")

;;;;;;;;;;;;;;;;;;;;;;;;
;; unit-tests summary ;;

(defn ("assert-summary")
    (if (= 0 tests-failed)
        (print tests-run "unit-tests passed")
        (err-print tests-failed "from" tests-run "unit-tests failed")
    )
)
(assert-summary)