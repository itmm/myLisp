(assert-setup)

(defn ("turing" "left" "head" "right" "states" "state")
    (def "result" (states head state))
    (def "state" (car result))
    (def "head" (cadr result))
    (def "move" (caddr result))
    (cond
        ((= move 1)
            (def "left" (cons head left))
            (def "head" (car right))
            (def "right" (cdr right))
            (def "head" (if head head 0))
            (turing left head right states state)
        )
        ((= move -1)
            (def "right" (cons head right))
            (def "head" (car left))
            (def "left" (cdr left))
            (def "head" (if head head 0))
            (turing left head right states state)
        )
        (else right)
    )
)

(defn ("minus-1" "in")
    (defn ("minus-1-fn" "head" "state") (0 0 0))
    (turing () (car in) (cdr in) minus-1-fn 0)
)

    (assert (= (minus-1 (1 1 1)) (1 1)))

(defn ("plus-1" "in")
    (defn ("plus-1-fn" "head" "state") (if
        state
        (if head (1 1 -1) (0 0 0))
        (if head (0 1 1) (1 1 -1))
    ))
    (turing () (car in) (cdr in) plus-1-fn 0)
)

    (assert (= (plus-1 (1 1 1)) (1 1 1 1)))

(assert-summary)