%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% River Crossing Puzzle: Farmer, Wolf, Goat, Cabbage %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% State representation: state(Farmer, Wolf, Goat, Cabbage)
% Each entity can only be LEFT or RIGHT
initial_state(state(left, left, left, left)).  % Everyone start on Left
goal_state(state(right, right, right, right)). % Goal: Everyone on Right

% Used to flip an entity to the other side
opposite(left, right).  % op(left,F1) match->op(left,right)->F1 bind to right
opposite(right, left).  % op(left,F1) match->op(left,right)->F1 bind to right

%%%% VALID MOVES %%%%%
% 1) Farmer goes ALONE
move(state(F, W, G, C), state(F1, W, G, C), 'Farmer crosses alone') :-
    opposite(F, F1), % Whatever is F1 gets flipped to other side
    safe(state(F1, W, G, C)).   % Check if new state is safe
% 2) Farmer takes WOLF
move(state(F, F, G, C), state(F1, F1, G, C), 'Farmer takes wolf') :-
    opposite(F, F1),
    safe(state(F1, F1, G, C)).
% 3) Farmer takes GOAT
move(state(F, W, F, C), state(F1, W, F1, C), 'Farmer takes goat') :-
    opposite(F, F1),
    safe(state(F1, W, F1, C)).
% 4) Farmer takes CABBAGE
move(state(F, W, G, F), state(F1, W, G, F1), 'Farmer takes cabbage') :-
    opposite(F, F1),
    safe(state(F1, W, G, F1)).
%%%%%% VALID MOVES (REVERSED ORDER) %%%%%
%%% 1) Farmer takes CABBAGE
%move(state(F, W, G, F), state(F1, W, G, F1), 'Farmer takes cabbage') :-
%    opposite(F, F1),
%    safe(state(F1, W, G, F1)).
%% 2) Farmer takes GOAT
%move(state(F, W, F, C), state(F1, W, F1, C), 'Farmer takes goat') :-
%    opposite(F, F1),
%    safe(state(F1, W, F1, C)).
%% 3) Farmer takes WOLF
%move(state(F, F, G, C), state(F1, F1, G, C), 'Farmer takes wolf') :-
%    opposite(F, F1),
%    safe(state(F1, F1, G, C)).
%% 4) Farmer goes ALONE
%move(state(F, W, G, C), state(F1, W, G, C), 'Farmer crosses alone') :-
%    opposite(F, F1),
%    safe(state(F1, W, G, C)).

%%% SAFETY CHECK - CANNOT BE ALONE %%%
% 1. Wolf & Goat  |  2. Goat & Cabbage
% "\=" = not equal  |  ";" = OR  |  "," = AND
safe(state(F, W, G, C)) :-
    (W \= G ; F = G),  % [Wolf NOT WITH Goat] OR[Farmer WITH Goat]
    (G \= C ; F = G).  % [Goat NOT WITH Cabbage] OR [Farmer WITH Goat]

%%%%% DISPLAY FUNCTIONS %%%%%
% Helper Predicate: Shows current positions on each side
describe_state(state(F, W, G, C)) :-
    write('Left bank: '),
    (F = left -> write('Farmer ') ; true),    % print Farmer  if on left
    (W = left -> write('Wolf ') ; true),      % print Wolf    if on left
    (G = left -> write('Goat ') ; true),      % print Goat    if on left
    (C = left -> write('Cabbage') ; true),    % print Cabbage if on left
    nl,                                       % NewLine
    write('Right bank: '),
    (F = right -> write('Farmer ') ; true),   % print Farmer  if on right
    (W = right -> write('Wolf ') ; true),     % print Wolf    if on right
    (G = right -> write('Goat ') ; true),     % print Goat    if on right
    (C = right -> write('Cabbage') ; true),   % print Cabbage if on right
    nl.                                       % NewLine

%%%%% SOLVER ALGORITHM: DFS %%%%%
solution(Path) :-
    initial_state(Start),               % Get starting state
    goal_state(Goal),                   % Get ending goal state
    solve(Start, Goal, [Start], Path).  % Find path from Start to Goal

% Base Case: Reached Goal State
solve(State, State, _, [State]).
% Recursive Case: Try next possible move
solve(State, Goal, Visited, [State | Path]) :-
    move(State, NextState, _),                % Try a valid move
    \+ member(NextState, Visited),            % Prevent cycles
    solve(NextState, Goal, [NextState | Visited], Path). % Continue search

%%%%% OUTPUT FORMATTING %%%%%
% Print full solution path with step descriptions
print_solution(Path) :-
    print_steps(Path, 1).  % Start with step 1

% Base case: No more steps to print
print_steps([_], _) :- !.  % Cut prevents backtracking
% Recursive case: Print current step and continue
print_steps([State1, State2 | Rest], StepNum) :-
    move(State1, State2, Description),                % Get move description
    format('Step ~w: ~w~n', [StepNum, Description]),  % Print StepNumber & Action
    describe_state(State2),                           % Show NewState
    nl,                                               % NewLine
    NextStep is StepNum + 1,                          % StepCounter++
    print_steps([State2 | Rest], NextStep).           % Continue to next step

%%%%% MAIN PROGRAM %%%%%
solve_puzzle :-
    initial_state(Initial),           % Get initial config
    write('Initial state:'), nl,
    describe_state(Initial),          % Display starting position
    nl,
    solution(Path),                   % Find solution path
    write('Solution found:'), nl,
    print_solution(Path),             % Print steps
    !.  % Cut to prevent multiple solutions / finding only 1st solution

% To run code:
% :- solve_puzzle.
