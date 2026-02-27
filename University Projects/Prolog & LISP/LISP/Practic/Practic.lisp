#|
interclasare(l1 l2 ... ln, m1 m2 ... mn) = { [], l si m sunt vide
					   { m1 (+) interclasare(NIL, m2...mn), l e vida si 						m1 e numar
					   { l1 (+) interclasare(l2...ln, NIL), m e vida si 						l1 e numar
					   { l1 (+) interclasare(l2...ln, m1 m2...mn), 
						l1 si m1 sunt numere si l1 <= m1
					   { m1 (+) interclasare(l1 l2...ln, m2..mn), 
						l1 si m1 sunt numere si m1 < l1
					   { interclasare(l1 l2...ln, m2...mn), l1 e numar 						si m1 nu e numar
					   { interclasare(l2...ln, m1 m2...mn), m1 e numar 						si l1 nu e numar
					   { interclasare(l2...ln, m2...mn), altfel
|#

(defun interclasare (l m)
	(cond
		( (and (null l) (null m)) NIL)
		( (null l) 
			(if (numberp (car m))
				(cons (car m) (interclasare NIL (cdr m)))
				(interclasare NIL (cdr m))
			)
		)
		( (null m)
			(if (numberp (car l))
				(cons (car l) (interclasare NIL (cdr l)))
				(interclasare NIL (cdr l))
			)
		)
		( (and (numberp (car l)) (numberp (car m)))
			(if (<= (car l) (car m))
				(cons (car l) (interclasare (cdr l) m))
				(cons (car m) (interclasare l (cdr m)))
			)
		)
		( (numberp (car l)) 
			(interclasare l (cdr m))
		)
		( (numberp (car m))
			(interclasare (cdr l) m)
		)
		(t (interclasare (cdr l) (cdr m)) )
	)
)