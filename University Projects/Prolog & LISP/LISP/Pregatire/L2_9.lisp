(defun parcurgere-stanga (l n m)
	(cond
		((null l) NIL)
		((= n (+ m 1)) NIL)
		(t (cons (car l) (cons (cadr l) (parcurgere-stanga (cddr l) (+ 1 n) (+ (cadr l) m)))) )
	)
)

(defun parcurgere-dreapta (l n m)
	(cond
		((null l) NIL)
		((= n (+ m 1)) l)
		(t (parcurgere-dreapta (cddr l) (+ 1 n) (+ (cadr l) m)) )
	)
)

(defun stanga (l)
	(parcurgere-stanga (cddr l) 0 0)
)

(defun dreapta (l)
	(parcurgere-dreapta (cddr l) 0 0)
)

(defun transform (l)
	(cond
 		((null l) NIL)
		(t (append (list (car l)) (list (transform (stanga l))) (list (transform (dreapta l)))) ) 
	)
)

(defun remove-NIL (l)
	(cond
		( (null l) NIL)
		( (null (car l)) (remove-NIL (cdr l)) )
		( (listp (car l)) (cons (remove-NIL (car l)) (remove-NIL (cdr l))) )
		(t (cons (car l) (remove-NIL (cdr l))) )
	)
)

(defun version2 (l)
	(remove-NIL (transform l))
)