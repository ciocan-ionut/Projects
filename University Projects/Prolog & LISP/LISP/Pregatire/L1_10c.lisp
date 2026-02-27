(defun inverseaza (s)
	(cond
		( (null s) NIL)
		(t (append (inverseaza (cdr s)) (list (car s))) )
	)
)

(defun parcurge-stiva (s result)
	(cond
		( (null s) (car result) )
		( (numberp (car s)) (parcurge-stiva (cdr s) (cons (car s) result)) )
		(t (parcurge-stiva (cdr s) (cons (funcall (car s) (car result) (cadr result)) (cddr result))) )
	)
)

(defun calculeaza (s)
	(parcurge-stiva (inverseaza s) NIL)
)