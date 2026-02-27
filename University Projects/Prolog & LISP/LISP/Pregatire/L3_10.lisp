#|
nivel-k(l k) = { 1, k = 0
	       { SUM:i=2,n nivel-k(li k-1), altfel
|#

(defun nivel-k (l k) 
	(cond
		( (= k 0) 1)
		(t (apply '+ (mapcar (lambda (v) (nivel-k v (- k 1))) (cdr l))) )
	)
)