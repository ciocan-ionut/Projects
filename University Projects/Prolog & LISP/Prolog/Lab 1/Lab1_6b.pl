% Elimina toate aparitiile elementului maxim din lista

% max(L:list, M:element)
% (i, o) - determinist
max([X], X).
max([H | T], M) :-
    max(T, M1), (H > M1 -> M = H; M = M1).

% eliminMaxAux(InitList:list, CurList:list, Rez:list)
% (i, i, o) - determinist
eliminMaxAux(_, [], []).
eliminMaxAux(InitList, [H | T], Rez) :-
    max(InitList, M), eliminMaxAux(InitList, T, Rez1),
    (H == M -> Rez = Rez1; Rez = [H | Rez1]).

% eliminMax(L:list, Rez:list)
% (i, o) - determinist
eliminMax([], []).
eliminMax(L, Rez) :-
    eliminMaxAux(L, L, Rez).
