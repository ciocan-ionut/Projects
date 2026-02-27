(defun verif-munte (l m)
	(cond
		( (null (cdr l)) 
			(if (= m 0)
				T
				NIL
			)
		)
		( (< (car l) (cadr l))
			(if (= m 0)
				NIL
				(verif-munte (cdr l) 1)
			)
		)
		( (> (car l) (cadr l)) 
			(if (= m -1)
				NIL
				(verif-munte (cdr l) 0)
			)	
		)
		(t NIL)
	)
)

(defun munte (l)
	(verif-munte l -1)
)