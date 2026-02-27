% Elimina elementele care apar de mai multe ori din lista

% nrAparitii(E:element, L:list, N:integer)
% (i, i, o) - determinist
nrAparitii(_, [], 0).
nrAparitii(E, [H | T], N) :-
    (E == H -> nrAparitii(E, T, N1), N is N1 + 1; nrAparitii(E, T, N)).

% eliminAux(InitList:list, CurList:list, Rez:list)
% (i, i, o) - determinist
eliminAux(_, [], []).
eliminAux(InitList, [H | T], Rez) :-
    nrAparitii(H, InitList, N), eliminAux(InitList, T, Rez1),
    (N =:= 1 -> Rez = [H | Rez1]; Rez = Rez1).

% elimin(L:list, Rez:list)
% (i, o) - determinist
elimin([], []).
elimin(L, Rez) :-
    eliminAux(L, L, Rez).
