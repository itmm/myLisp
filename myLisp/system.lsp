;; this file defines basic functions

(def one 1)
(def two 2)

(def defn (fn (name args body) (def name (fn args body))))
