#|
substituire(l e l1) = { l1, l = e
		      { l, l e atom
		      { U:i=1,n substituire(li e l1), altfel
|#

(defun substituire (l e l1)
	(cond
		( (equal e l) l1)
		( (atom l) l)
		(t (mapcar (lambda (v) (substituire v e l1)) l) )
	)
)