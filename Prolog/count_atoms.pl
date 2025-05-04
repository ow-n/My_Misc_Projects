% Count number of atoms in List (including nested lists)
% count_atom(List, Count)

% Notes on Prolog
% - atom(arg) returns true if arg is atomic
% eg. atom(abc) = true, atom(123) & atom([a,b]) = false
% - atomic(arg) returns true if arg is an atomic term (atom/num/empty
% list)
% eg. atomic(abc), atomic(123), atomic([]) = true
% - "\+" = negatation
% - "!" = cut (prevent backtracking, won't try alternative clauses)

% Base Case: Empty List = 0
count_atom([], 0).

% Atom Case: If current element is an atom, count it as 1
count_atom([H|Tail], N) :-
    atomic(H),
    !,  % Cut when H is atomic
    count_atom(Tail, N1),
    N is N1 + 1.

% List Case: If current element is a list, recursively count its atoms
count_atom([H|Tail], N) :-
    is_list(H),
    !,  % Cut when H is a list
    count_atom(H, N1),
    count_atom(Tail, N2),
    N is N1 + N2.

% Example Usage:
% ?- count_atom([],N).
% N = 0.
%
% ?- count_atom([a,b,c],N).
% N = 3.
%
% ?- count_atom([a,b,c,[1,2,3]],N).
% N = 6.
