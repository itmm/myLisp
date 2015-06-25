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

(defm if (cnd block else) (cond cnd block true else))

(defn sum (n) (if (= n) 0 (+ n (sum (- n 1)))))
