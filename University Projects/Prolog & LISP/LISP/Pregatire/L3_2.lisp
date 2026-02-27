#|
aplatizare(l) = { (l), l e atom
		{ U:i=1,n aplatizare(li), altfel
|#

(defun aplatizare (l)
	(cond
		( (atom l) (list l))
		(t (mapcan 'aplatizare l) )
	)
)