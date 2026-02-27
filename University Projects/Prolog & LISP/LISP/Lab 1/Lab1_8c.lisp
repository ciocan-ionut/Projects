#|
selecteazaAtomi(l1 l2...ln) = { [], l e vida
			      { l1 (+) selecteazaAtomi(l2...ln), l1 e atom
			      { selecteazaAtomi(l1) (+) selecteazaAtomi(l2...ln), altfel
|#
(defun selecteazaAtomi (lst)
(cond
    ((null lst) NIL)
    ((atom (car lst)) 
	(cons (car lst) (selecteazaAtomi (cdr lst))))
    (t 
	(append (selecteazaAtomi (car lst)) (selecteazaAtomi (cdr lst))))))

#|
nrAparitii(e, l1 l2...ln) = { 0, l e vida
			    { 1 + nrAparitii(e, l2...ln), l1 = e
			    { nrAparitii(e, l2...ln), altfel
|#
(defun nrAparitii (e lst)
(cond
    ((null lst) 0)
    ((= e (car lst))
	(+ 1 (nrAparitii e (cdr lst))))
    (t
	(nrAparitii e (cdr lst)))))

#|
eliminaDubluri(l1 l2...ln) = { [], l e vida
			     { eliminaDubluri(l2...ln), nrAparitii(l1, l1...ln) > 1
			     { eliminaDubluri(l2...ln) (+) l1, altfel
|#
(defun eliminaDubluri (lst)
(cond
    ((null lst) NIL)
    ((> (nrAparitii (car lst) lst) 1)
	(eliminaDubluri (cdr lst)))
    (t
	(append (eliminaDubluri (cdr lst)) (list (car lst))))))

;; creareMultimeAtomi(l) = eliminaDubluri(inverseazaLista(selecteazaAtomi(l)))
(defun creareMultimeAtomi (lst)
    (eliminaDubluri (inverseazaLista (selecteazaAtomi lst))))
    