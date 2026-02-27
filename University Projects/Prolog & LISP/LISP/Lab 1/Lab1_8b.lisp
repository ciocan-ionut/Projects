#|
inverseazaLista(l1 l2...ln) = { [], l e vida
			      { inverseazaLista(l2...ln) (+) l1, altfel
|#
(defun inverseazaLista (lst)
(cond
    ((null lst) NIL)
    (t (append (inverseazaLista (cdr lst)) (list (car lst))))))

#|
calcSuccesor(c, l1 l2...ln) = { [], l e vida & c = 0
			      { (1), l e vida & c = 1
			      { calcSuccesor(1, l2...ln) (+) l1 + c - 10, l1 + c >= 10
			      { calcSuccesor(0, l2...ln) (+) l1 + c, altfel 
|#
(defun calcSuccesor (c lst) 
(cond
    ((null lst) 
        (cond 
            ((= c 1) (list 1))
	    (t NIL)))
    ((>= (+ (car lst) c) 10) 
	(append (calcSuccesor 1 (cdr lst)) (list (- (+ (car lst) c) 10))))
    (t 
	(append (calcSuccesor 0 (cdr lst)) (list (+ (car lst) c))))))
    
;; succesor(l) = calcSuccesor(1, inverseazaLista(l))
(defun succesor (lst)
    (calcSuccesor 1 (inverseazaLista lst)))