% Knight's Tour for 8x8 chessboard using production system architecture
% Based on Chapter 6 principles

% How to run:
% ?- solve_knight_path((1,1), (1,4)).
% ?- solve_rev_knight_path((1,1), (1,4)).

%%% DEFINE LEGAL KNIGHT MOVES %%%
knight_move(2, 1).  % works by adding to original coordinate
knight_move(2, -1).
knight_move(-2, 1).
knight_move(-2, -1).
knight_move(1, 2).
knight_move(1, -2).
knight_move(-1, 2).
knight_move(-1, -2).
rev_knight_move(-1, -2).  % REVRESED ORDER
rev_knight_move(-1, 2).
rev_knight_move(1, -2).
rev_knight_move(1, 2).
rev_knight_move(-2, -1).
rev_knight_move(-2, 1).
rev_knight_move(2, -1).
rev_knight_move(2, 1).

%% Check if position is on 8x8 board %%
on_board(Row, Col) :-
    Row >= 1, Row =< 8,
    Col >= 1, Col =< 8.

%% PRODUCTION RULE %%
% Generate valid moves from one position to another
move((R1, C1), (R2, C2)) :-
    knight_move(DR, DC),
    R2 is R1 + DR,
    C2 is C1 + DC,
    on_board(R2, C2).
rev_move((R1, C1), (R2, C2)) :-  % REVRESED ORDER
    rev_knight_move(DR, DC),
    R2 is R1 + DR,
    C2 is C1 + DC,
    on_board(R2, C2).

% ProductionRule: BASE CASE for path finding (already at destination)
path(Pos, Pos, Visited, Visited).
% Production rule: RECURSIVE CASE for path finding (take a step)
path(Current, Destination, Visited, FinalPath) :-
    move(Current, NextPos),
    \+ member(NextPos, Visited),  % dont revisit squares
    path(NextPos, Destination, [NextPos|Visited], FinalPath).
rev_path(Pos, Pos, Visited, Visited).  % REVERSED ORDER
rev_path(Current, Destination, Visited, FinalPath) :-
    rev_move(Current, NextPos),
    \+ member(NextPos, Visited),  % dont revisit squares
    rev_path(NextPos, Destination, [NextPos|Visited], FinalPath).

% Find a path between two positions (original order)
find_path(Start, End, Path) :-
    path(Start, End, [Start], RevPath),
    reverse(RevPath, Path).
find_rev_path(Start, End, Path) :-  % REVERSED ORDER
    rev_path(Start, End, [Start], RevPath),
    reverse(RevPath, Path).

% Print List of Positions
print_path([]).
print_path([Pos|Rest]) :-
    write(Pos), nl,
    print_path(Rest).

% Wrapper predicate that doesn't return Path
solve_knight_path(Start, End) :-
    find_path(Start, End, Path),
    print_path(Path),
    write('GOAL FOUND'), nl.
solve_rev_knight_path(Start, End) :-  % REVERSED ORDER
    find_rev_path(Start, End, Path),
    print_path(Path),
    write('GOAL FOUND'), nl.

%%% KNIGHT'S TOUR %%%
knights_tour(Start, Tour) :-
    knights_tour_helper(Start, [Start], Tour).
knights_tour_helper(_, Visited, Tour) :-
    length(Visited, 64),  % all squares visited
    reverse(Visited, Tour).
knights_tour_helper(Current, Visited, Tour) :-
    length(Visited, N),
    N < 64,
    move(Current, NextPos),
    \+ member(NextPos, Visited),
    knights_tour_helper(NextPos, [NextPos|Visited], Tour).
