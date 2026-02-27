% This buffer is for notes you don't want to save.
% If you want to create a file, visit that file with C-x C-f,
% then enter the text in that file's own buffer.

% detSubsiruriCresc(L:list, Sub:list)
% (i, o) - nedeterminist
detSubsiruriCresc([], []) :- !.
detSubsiruriCresc(L, Sub) :-
    genSubliste(L, Sub),
    sublistaCresc(Sub),
    length(Sub, Length), Length >= 2.

% genSubliste(L:list, Sub:list)
% (i, o) - nedeterminist
genSubliste([], []).
genSubliste([H | T], [H | Sub]) :-
    genSubliste(T, Sub).
genSubliste([_ | T], Sub) :-
    genSubliste(T, Sub).

% sublistaCresc(L:list)
% (i, o) - determinist
sublistaCresc([]) :- !.
sublistaCresc([_]):- !.
sublistaCresc([A, B | T]) :-
    !, A < B, sublistaCresc([B | T]).
