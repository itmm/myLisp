;; this file defines basic functions

(def one 1)
(def two 2)

(def defn (fn macro (name args body) (def (eval name) (fn args body))))
(def defm (fn macro (name args body) (def (eval name) (fn macro args body))))

(defn cons (a b) (list a . b))
(defn caar (x) (car (car x)))
(defn caaar (x) (car (car (car x))))

(defm if (cnd block else) (cond cnd block true else))
