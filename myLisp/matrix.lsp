(assert-setup)

(defn ("loop" "n" "generator")
    (defn ("iterator" "i")
        (if (> i n)
            ()
            (cons (generator i) (iterator (+ i 1)))
        )
    )
    (iterator 1)
)

(defn ("vec-1" "n" "i")
    (loop n (fn ("j")
        (if (= i j) 1 0)
    ))
)

    (assert (= (vec-1 4 1) (1 0 0 0)) "vec-1 4 1")
    (assert (= (vec-1 4 4) (0 0 0 1)) "vec-1 4 4")
    (assert (= (vec-1 1 1) (1)) "vec-1 1 1")

(defn ("vec-0" "n")
    (loop n (fn "i" 0))
)

    (assert (= (vec-0 4) (0 0 0 0)) "vec-zero 4")
    (assert (= (vec-0 1) (0)) "vec-0 1")

(defn ("combine" "as" "bs" "f")
    (if (null? as)
        ()
        (cons (f (car as) (car bs)) (combine (cdr as) (cdr bs) f))
    )
)

(defn ("vec-add" "as" "bs")
    (combine as bs +)
)

    (assert (= (vec-add (1 2 3) (2 5 7)) (3 7 10)) "vec-add (1 2 3) (2 5 7)")

(defn ("vec-sub" "as" "bs")
    (combine as bs -)
)

    (assert (= (vec-sub (vec-1 7 1) (vec-1 7 1)) (vec-0 7)) "vec-sub (vec-1 7 1) (vec-1 7 1)")

(defn ("collect-2" "as" "bs" "f" "init")
    (if (null? as)
        init
        (f (car as) (car bs) (collect-2 (cdr as) (cdr bs) f init))
    )
)

(defn ("vec-dot" "as" "bs")
    (collect-2 as bs (fn ("a" "b" "s")
        (+ (* a b) s)
    ) 0)
)

    (assert (= (vec-dot (1 2 3) (2 3 4)) 20) "vec-dot (1 2 3) (2 3 4)")

(defn ("map" "as" "f")
    (if (null? as)
        ()
        (cons (f (car as)) (map (cdr as) f))
    )
)

(defn ("vec-scalar-mult" "as" "x")
    (map as (fn ("a") (* a x)))
)

    (assert (= (vec-scalar-mult (1 2 3) 3) (3 6 9)) "vec-scalar-mult (1 2 3) 3")
    (assert (= (vec-scalar-mult (vec-1 7 3) -1) (vec-sub (vec-0 7) (vec-1 7 3))) "vec-scalar-mult -1")

(defn ("mtx-1" "n")
    (loop n (fn ("i")
        (vec-1 n i)
    ))
)

    (assert (= (mtx-1 3) ((1 0 0) (0 1 0) (0 0 1))) "mtx-1 3")
    (assert (= (mtx-1 1) ((1))) "mtx-1 1")

(defn ("mtx-0" "n")
    (loop n (fn ("i")
        (vec-0 n)
    ))
)

    (assert (= (mtx-0 3) ((0 0 0) (0 0 0) (0 0 0))) "mtx-0 3")

(defn ("mtx-add" "as" "bs")
    (combine as bs vec-add)
)
(defn ("mtx-sub" "as" "bs")
    (combine as bs vec-sub)
)
(defn ("mtx-scalar-mult" "as" "x")
    (map as (fn ("a") (vec-scalar-mult a x)))
)

    (assert (= (mtx-scalar-mult (mtx-1 7) 0) (mtx-0 7)) "0 * I7")
    (assert (= (mtx-scalar-mult (mtx-1 9) -1) (mtx-sub (mtx-0 9) (mtx-1 9))) "-1 * I == 0 - I")

    (defn ("add-lists" "as" "bs")
        (if (null? as)
            bs
            (cons (car as) (add-lists (cdr as) bs))
        )
    )

(defn ("mtx-transpose" "ms")
    (defn ("add-col-to-rows" "vs" "rs")
        (if (null? vs)
            ()
            (cons
                (add-lists (car rs) (list (car vs)))
                (add-col-to-rows (cdr vs) (cdr rs))
            )
        )
    )
    (defn ("helper" "cols" "rows")
        (if (null? cols)
            rows
            (helper (cdr cols) (add-col-to-rows (car cols) rows))
        )
    )
    (helper ms ())
)

    (assert (= (mtx-transpose ((1 2 3) (4 5 6))) ((1 4) (2 5) (3 6))) "transpose")

(defn ("mtx-mult" "as" "bs")
    (let (("ts" (mtx-transpose as)))
        (mtx-transpose (map ts (fn ("t")
            (map bs (fn ("b")
                (vec-dot t b)
            ))
        )))
    )
)

    (assert (= (mtx-mult ((1 3) (2 4)) ((5 6))) ((17 39))) "matrix times vector")

(assert-summary)