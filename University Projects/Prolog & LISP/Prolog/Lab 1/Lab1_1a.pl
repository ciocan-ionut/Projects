% diferenta(L:list, E:element, R:list)
diferenta([], _) :- !.
diferenta([H | T], E) :-
    H =\= E, !, diferenta(T, E).

% diferenta_multimi(L1:list, L2:list, R:list)
diferenta_multimi([], _, []) :- !.
diferenta_multimi([H | T], L2, [H | R]) :-
    diferenta_multimi(T, L2, R), diferenta(L2, H), !.
diferenta_multimi([_ | T], L2, R) :-
    diferenta_multimi(T, L2, R).
