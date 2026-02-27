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

(defun inordine (l)
	(cond
		((null l) NIL)
		(t (append (inordine (stanga l)) (list (car l)) (inordine (dreapta l))) )
	)
)