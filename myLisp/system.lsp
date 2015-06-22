;; this file defines basic functions

(def defn (fn macro (name args body) (def (eval name) (fn args body))))
(def defm (fn macro (name args body) (def (eval name) (fn macro args body))))

(defn cons (a b) (list a . b))
(defn caar (x) (car (car x)))
(defn caaar (x) (car (car (car x))))

(defm if (cnd block else) (cond cnd block true else))

(defn sum (n) (if (= n) 0 (+ n (sum (- n 1)))))
