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

;;;;;;;;;;;;;
;; newline ;;

(def "str-newline" "
")

(defn ("newline") (print str-newline))

(defn ("err-newline") (err-print str-newline))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; assert can be used for unit-tests ;;

(def "tests-run" 0)
(def "tests-failed" 0)

(defn ("assert-setup")
    (def "tests-run" 0)
    (def "tests-failed" 0)
)

(def "else" true)

(defm ("assert" "cnd")
    (def "tests-run" (+ 1 tests-run))
    (cond
        (cnd true)
        (else
            (def "tests-failed" (+ 1 tests-failed))
            (err-print (quote cnd) " not working" str-newline)
        )
    )
)

;;;;;;;;;;;;;;;;;
;; build lists ;;

(defn ("cons" "a" "b") (list a . b))

    (assert (= (cons 1 (2 3)) (1 2 3)))
    (assert (= (cons 1 ()) (1)))

;;;;;;;;;;;;;;;;;;;;;;;;
;; car/cdr shorthands ;;

(defn ("caar" "x") (car (car x)))

    (assert (= (caar ((1) 2)) 1))

(defn ("cadr" "x") (car (cdr x)))

    (assert (= (cadr (1 2 3)) 2))

(defn ("cdar" "x") (cdr (car x)))

    (assert (= (cdar ((1 2) 3)) (2)))

(defn ("cddr" "x") (cdr (cdr x)))

    (assert (= (cddr (1 2 3)) (3)))

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

    (assert (= (1+ 5) 6))

(defm ("if" "condition" "true-block" "false-block") (cond (condition true-block) (else false-block)))

    (assert (= (if true 3 4) 3))
    (assert (= (if false 3 4) 4))

(defn ("sum" "n") (if (= n) 0 (+ n (sum (- n 1)))))

(def "nil" '())

(defn ("null?" "lst") (= () lst))

    (assert (= (null? nil) true))
    (assert (= (null? (1)) false))
    (assert (= (null? 0) false))
    (assert (= (null? "()") false))

(defn ("apply" "f" "args") (f . args))

    (assert (= (apply + (2 3 4)) 9))

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

    (assert (= (flatten) (list)))
    (assert (= (flatten 1 2) (1 2)))
    (assert (= (flatten (1 2) (3)) (1 2 3)))


;;;;;;;;;;
;; bool ;;

(defm ("and" "a" "b" . "args") (if a
    (if (null? args)
        b
        (and b . args)
    )
    a
))

    (assert (= (and false false) false))
    (assert (= (and false true) false))
    (assert (= (and true false) false))
    (assert (= (and true 1) true))

    (assert (= (and 1 2 3 4) 4))

(defm ("or" "a" "b" . "args") (if a
    a
    (if (null? args)
        b
        (or b . args)
    )
))

    (assert (= (or 1 (err-print "or is not short-circuing" str-newline)) 1))
    (assert (= (or 0 false 2) 2))
    (assert (= (or false 0) 0))

(defn ("not" "a") (false? a))

    (assert (= (not 1) false))
    (assert (= (not 0) true))

(defn ("xor" "a" "b" . "args") (if a
    (if (null? args) (not b) (not (xor b . args)))
    (if (null? args) (true? b) (xor b . args))
))

    (assert (= (xor 0 0) false))
    (assert (= (xor 0 1) true))
    (assert (= (xor 1 0) true))
    (assert (= (xor 1 1) false))

    (assert (= (xor 0 1 0) true))


;;;;;;;;;;;;;;;;;;;;;;;
;; filter & listable ;;

(defn ("filter" "lst" "ref" "op") (cond
    ((= (list) lst) (list))
    ((op (car lst) ref) (cons (car lst) (filter (cdr lst) ref op)))
    (else (filter (cdr lst) ref op))
))

    (assert (= (filter (1 2 3 4) 3 <) (1 2)))
    (assert (= (filter (4 3 2 1) 3 <) (2 1)))

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

    (assert (= (<= 2 2) true))
    (assert (= (<= 2 3) true))
    (assert (= (<= 3 2) false))
    (assert (= (<= 1 2 2 3) true))
    (assert (= (<= 1 2 1) false))
    (assert (= (<= 2 1 (err-print "<= lazy not working" str-newline)) false))

(defm (">" . "args") (listable (fn ("a" "b") (< b a)) . args))

    (assert (= (> 5 4 3) true))
    (assert (= (> 5 4 5) false))

(defm (">=" . "args") (listable (fn ("a" "b") (or (= a b) (< b a))) . args))

    (assert (= (>= 5 4 4) true))
    (assert (= (>= 5 4 5) false))

(defn ("sort" . "a") (cond
    ((= (list) a) a)
    ((= (list) (cdr a)) a)
    (else (flatten
        (apply sort (filter (cdr a) (car a) <=))
        (list (car a))
        (apply sort (filter (cdr a) (car a) >))
    ))
))

    (assert (= (sort 8 3 5 7 2) (2 3 5 7 8)))

;; doubles is a helper method for ><

(defn ("doubles" "a") (cond
    ((= (list) a) false)
    ((= (list) (cdr a)) false)
    ((= (car a) (cadr a)) true)
    (else (doubles (cdr a)))
))

    (assert (= (doubles (2 3 3 5)) true))
    (assert (= (doubles (2 3 5)) false))
    (assert (= (doubles ()) false))
    (assert (= (doubles (2)) false))

(defn ("><" . "a") (not (doubles (apply sort a))))

    (assert (= (>< 1 2 3) true))
    (assert (= (><) true))
    (assert (= (><) 1))
    (assert (= (>< 2 1 2) false))


;;;;;;;;
;; do ;;

(defm ("do" . "statements") (cond (true . statements)))

    (assert (= (do (+ 1 2) (+ 2 3)) 5))


;;;;;;;;;;
;; sign ;;

(defn ("sign" "a") (if (number? a)
    (cond
        ((= a 0) 0)
        ((< a 0) -1)
        (else 1)
    )
    (error "argument must be numeric")
))

    (assert (= (sign 5) 1))
    (assert (= (sign 0) 0))
    (assert (= (sign -3) -1))

(assert (import "tests.lsp"))
(assert (import "sicp-tests.lsp"))


;;;;;;;;;;;;;;;;
;; str-length ;;

(defn ("str-length" . "args")
    (_str-length (str-print . args))
)

    (assert (= (str-length) 0))
    (assert (= (str-length 1 2 3) 3))

;;;;;;;;;;;;;
;; min/max ;;

(defn ("collect" "values" "init" "f")
    ((fn ("rest" "result")
        (if (null? rest)
            result
            (self (cdr rest) (f (car rest) result))
        )
    ) values init)
)

(defn ("max" . "args")
    (collect (cdr args) (car args) (fn ("value" "result")
        (if (< result value) value result)
    ))
)

    (assert (= (max 1 4 2) 4))
    (assert (= (max 3) 3))

(defn ("min" . "args")
    (collect (cdr args) (car args) (fn ("value" "result")
        (if (< value result) value result)
    ))
)

    (assert (= (min 2 1 3) 1))
    
;;;;;;;;;;;;;;;;;;;;;;;;
;; unit-tests summary ;;

(defn ("assert-summary")
    (if (= 0 tests-failed)
        (print tests-run " unit-tests passed" str-newline)
        (err-print tests-failed " from " tests-run " unit-tests failed" str-newline)
    )
)
(assert-summary)