#|
adancime(arbore) = { 0, arbore e atom
		   { 1 + MAX:i=2,n adancime(li), altfel
|#

(defun adancime (arbore)
	(cond
		( (atom arbore) 0)
		(t (+ 1 (apply 'max (cons 0 (mapcar 'adancime (cdr arbore))))) )
	)
)