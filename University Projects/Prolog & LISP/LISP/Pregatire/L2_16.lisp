(defun inaltime (arbore)
	(cond
		( (null arbore) 0)
		(t (+ 1 (max (inaltime (cadr arbore)) (inaltime (caddr arbore))) )
	)
)

(defun echilibrat (l)
	(cond
		( (null l) T)
		( (< 1 (abs (- (inaltime (cadr l)) (inaltime (caddr l)) ) ) ) 
			NIL
		)
		(t (and (echilibrat (cadr l)) (echilibrat (caddr l))) )
	)
)