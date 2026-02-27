#|
preordine(l1 l2 l3) = { [], l e vida
		      { l1 (+) preordine(l2) (+) preordine(l3), altfel
|#
(defun preordine (l)
   (cond
       ((null l) NIL)
       (t (append (list (car l)) (preordine (cadr l)) (preordine (caddr l))))
   )
)