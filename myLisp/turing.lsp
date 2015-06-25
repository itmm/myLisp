(defn turing (left head right states state) (do
    (def result (states head state))
    (def state (car result))
    (def head (cadr result))
    (def move (caddr result))
    (cond
        (= move 1) (do
            (def left (cons head left))
            (def head (car right))
            (def right (cdr right))
            (def head (cond head head true 0))
            (turing left head right states state)
        )
        (= move -1) (do
            (def right (cons head right))
            (def head (car left))
            (def left (cdr left))
            (def head (cond head head true 0))
            (turing left head right states state)
        )
        true right
    )
))

(defn minus-1-fn (head state) (list 0 0 0))

(defn minus-1 (in) (turing (list) (car in) (cdr in) minus-1-fn 0))

(defn plus-1-fn (head state) (cond
    (= state 0)
    (cond
        (= head 1) (list 0 1 1)
        true (list 1 1 -1)
    )
    true
    (cond
        head (list 1 1 -1)
        true (list 0 0 0)
    )
))

(defn plus-1 (in) (turing (list) (car in) (cdr in) plus-1-fn 0))
