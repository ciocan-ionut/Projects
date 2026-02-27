#|
eliminaPozN (n, l1 l2...ln) = { [], l e vida
			      { eliminaPozN(n-1, l2...ln), n = 0
			      { l1 (+) eliminaPozN(n-1, l2...ln), altfel
|#
(defun eliminaPozN (n lst)
    (cond
        ((null lst) nil)
	((= n 0) (cdr lst))
	(t (cons (car lst) (eliminaPozN (- n 1) (cdr lst))))))