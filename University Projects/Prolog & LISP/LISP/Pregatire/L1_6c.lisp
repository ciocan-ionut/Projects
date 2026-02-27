(defun calc-subliste (l)
	(cond
		( (null l) 0)
		( (atom (car l)) (calc-subliste (cdr l)))
		(t (+ (+ 1 (calc-subliste (car l))) (calc-subliste (cdr l))) )
	)
)

(defun nr-subliste (l)
	(+ 1 (calc-subliste l))
)