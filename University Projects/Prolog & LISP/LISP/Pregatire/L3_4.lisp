#|
suma(l) = { 0, l e atom
	  { l, l e numar
	  { SUM:i=1,n suma(li), altfel
|#

(defun suma (l)
	(cond
		( (numberp l) l)
		( (atom l) 0) 
		(t (apply '+ (mapcar 'suma l)) )
	)
)