% Count number of elements in List
% count_el(List, Count)

% Base Case: Empty List = 0
count_el([], 0).

% Recursive Case:
%   recursively call 'count_el' until N1 binds to BaseCase:0
%   N1 now has a value, so N is 1(0+1)
%   then resursion resolves up, updating N1
count_el([_|Tail], N) :-
    count_el(Tail, N1),
    N is N1 + 1.

% How it's different from iterative programs
% Instead of returning values,
% it uses unification to bind values to variables
% and the bindings propogate through entire query.

% Example Usage:
% ?- count_el([],N).
% N = 0.
%
% ?- count_el([a,b,c],N).
% N = 3.
%
% ?- count_el([a,b,c,[1,2,3]],N).
% N = 4.
