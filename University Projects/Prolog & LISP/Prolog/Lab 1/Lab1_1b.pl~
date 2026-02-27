% adaugaDupaElemPar(L:list, R:list)
adaugaDupaElemPar([], []) :- !.
adaugaDupaElemPar([H | T], [H, 1 | R]) :-
    H mod 2 =:= 0, !, adaugaDupaElemPar(T, R).
adaugaDupaElemPar([H | T], [H | R]) :-
    adaugaDupaElemPar(T, R).
