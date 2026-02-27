#|
verifMultime(l1 l2...ln) = { Adevarat, l e vida
			   { Fals, nrAparitii(l1, l1...ln) > 1
			   { verifMultime(l2...ln), altfel
|#
(defun verifMultime (lst)
(cond
    ((null lst) T)
    ((< 1 (nrAparitii (car lst) lst)) NIL)
    (t (verifMultime (cdr lst)))))