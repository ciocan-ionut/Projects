(defun calc-suma (l1 l2 c)
	(cond
		( (and (null l1) (null l2)) NIL
			(if (= c 0)
				NIL
				(list 1)
			)
		)
		( (null l1) 
			(if (<= 10 (+ c (car l2)))
				(append (list (mod (+ c (car l2)) 10)) (calc-suma NIL (cdr l2) 1))
				(append (list (+ c (car l2))) (calc-suma NIL (cdr l2) 0))
			)
		) 
		( (null l2) 
			(if (<= 10 (+ c (car l1)))
				(append (list (mod (+ c (car l1)) 10)) (calc-suma (cdr l1) NIL 1))
				(append (list (+ c (car l1))) (calc-suma (cdr l1) NIL 0))
			)
		)
		( (<= 10 (+ c (car l1) (car l2)))
			(append (list (mod (+ c (car l1) (car l2)) 10)) (calc-suma (cdr l1) (cdr l2) 1))
		)
		(t (append (list (+ c (car l1) (car l2))) (calc-suma (cdr l1) (cdr l2) 0)) )
	)
)

(defun inverseaza (l)
	(cond
		( (null l) NIL )
		(t (append (inverseaza (cdr l)) (list (car l))))
	)
)

(defun transform (l p)
	(cond
		( (null l) 0)
		(t (+ (* p (car l)) (transform (cdr l) (* p 10))) )
	)
)

(defun suma (l1 l2)
	(transform (calc-suma (inverseaza l1) (inverseaza l2) 0) 1)
)

