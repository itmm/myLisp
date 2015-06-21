;; this file defines basic functions

(def one 1)
(def two 2)

(def defn (fn macro (name args body) (def (eval name) (fn args body))))
