;; this file defines basic functions

(def defn (fn macro (name args body) (def (eval name) (fn args body))))
(def defm (fn macro (name args body) (def (eval name) (fn macro args body))))

(defn cons (a b) (list a . b))
(defn caar (x) (car (car x)))
(defn cadr (x) (car (cdr x)))
(defn cdar (x) (cdr (car x)))
(defn cddr (x) (cdr (cdr x)))
(defn caaar (x) (car (car (car x))))
(defn caadr (x) (car (car (cdr x))))
(defn cadar (x) (car (cdr (car x))))
(defn caddr (x) (car (cdr (cdr x))))
(defn cdaar (x) (cdr (car (car x))))
(defn cdadr (x) (cdr (car (cdr x))))
(defn cddar (x) (cdr (cdr (car x))))
(defn cdddr (x) (cdr (cdr (cdr x))))

(defn 1+ (x) (+ 1 x))

(defm if (cnd block else) (cond (eval cnd) (eval block) true (eval else)))

(defn sum (n) (if (= n) 0 (+ n (sum (- n 1)))))
(defn assert (cnd msg) (cond cnd true true (err-print msg)))

(print "running unit tests")
(assert (= (if true 3 4) 3) "if true not working")
(assert (= (if false 3 4) 4) "if false not working")
(print "done with unit tests")
