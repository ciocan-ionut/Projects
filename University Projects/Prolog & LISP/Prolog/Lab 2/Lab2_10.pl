% testarePozitie(P:element)
% (i) - determinist
testarePozitie(1).
testarePozitie(P) :-
    P > 1, OtP is P + 1, (0 is OtP /\ P).

% inserareElement(E:element, L:list, R:list)
% (i, i, o) - determinist
inserareElement(_, [], []) :- !.
inserareElement(E, L, R) :-
    inserareElementAux(E, L, 1, R).

% inserareElementAux(E:element, L:list, P:element, R:list)
% (i, i, i, o) - determinist
inserareElementAux(_, [], _, []) :- !.
inserareElementAux(E, [H | T], P, [H, E | Rez1]) :-
    testarePozitie(P), !, P1 is P + 1, inserareElementAux(E, T, P1, Rez1).
inserareElementAux(E, [H | T], P, [H | Rez1]) :-
    \+ testarePozitie(P), P1 is P + 1, inserareElementAux(E, T, P1, Rez1).

% inserareListaEterogena(L:list, R:list)
% (i, o) - determinist
inserareListaEterogena([], []) :- !.
inserareListaEterogena(L, R) :-
    inserareAux(L, _, R).

% inserareAux(L:list, E:element, R:list)
% (i, i, o) - determinist
inserareAux([], _, []) :- !.
inserareAux([H | T], E, [R | Rez1]) :-
    is_list(H), !, inserareElement(E, H, R), inserareAux(T, E, Rez1).
inserareAux([H | T], _, [H | Rez1]) :-
    number(H), inserareAux(T, H, Rez1).

