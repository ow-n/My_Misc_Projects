% Wirth's "I am my own grandfather"

% Facts
male(i).
male(f).
male(s1).
male(s2).
female(w).
female(d).

married(i, w).  % “I married a widow (w)...”
mother(w, d).   %     “...widow had a daughter (d)”
father(f, i).   % “My father (f)...”
married(f, d).  %   “...my father married my stepdaughter (d)”
mother(w, s1).  % “My wife w gave birth to a son (s1)”
mother(d, s2).  % “The wife of my father (d) also had a son (s2)”

% Rules
spouse(X,Y) :- married(X,Y).
spouse(X,Y) :- married(Y,X).
% directParent = father or mother
directParent(X, Y) :- father(X, Y).
directParent(X, Y) :- mother(X, Y).

father_in_law(X, Y) :-
    father(X, Z),  % "X is father of Z"
    spouse(Z, Y).  % "Z is spouse of Y"

father_in_law(X, Y) :-  % "X is male, spouse of Z, Z is a directParent of Y"
    male(X),                % "X is male"
    spouse(X, Z),           % "X is spouse of Z"
    directParent(Z, Y),     % "Z is directParent of Y"
    \+ directParent(X, Y).  % "X is NOT directParent of Y"

mother_in_law(X, Y) :-
    mother(X, Z),  % "X is mother of Z"
    spouse(Z, Y).  % "Z is spouse of Y"

mother_in_law(X, Y) :-
    female(X),             % "X is female"
    spouse(X, Z),          % "X is spouse of Z"
    directParent(Z, Y),    % "Z is directParent of Y"
    \+ directParent(X, Y). % "X is NOT directParent of Y"

parent(X, Y) :- directParent(X, Y).
parent(X, Y) :- father_in_law(X, Y).
parent(X, Y) :- mother_in_law(X, Y).

grandfather(X, Y) :-
    male(X),
    parent(X, Z),
    parent(Z, Y).

