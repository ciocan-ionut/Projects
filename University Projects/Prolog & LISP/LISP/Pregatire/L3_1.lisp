#|
adancime(l) = { 0, l e atom
	      { 1 + MAX:i=1,n adancime(li), altfel
|#

(defun adancime (l)
	(cond
		( (atom l) 0 )
		(t (+ 1 (apply 'max (mapcar 'adancime l))))
	)
)