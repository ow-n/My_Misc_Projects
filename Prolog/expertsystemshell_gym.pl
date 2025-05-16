%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%  Rule Based Expert System Shell  %%%%%%
%%%%%            Gym-Coach             %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Start Program:
% ?- solve(training_advice(X)).
%   - initializes working memory
%   - attempts to solve Goal with certainty factor
%   - prints results
%   - asks user if they would like a trace

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

solve(Goal) :-
    init, print_help,
    solve(Goal,C,[],1),
    nl,write('Solved '),write(Goal),
    write(' With Certainty = '),write(C),nl,nl,
    ask_for_trace(Goal).

% init
% purges all facts from working memory.

init :- retractm(fact(X)), retractm(untrue(X)).

% solve(Goal,CF,Rulestack,Cutoff_context)
% Attempts to solve Goal by backwards chaining on rules;  CF is
% certainty factor of final conclusion; Rulestack is stack of
% rules, used in why queries, Cutoff_context is either 1 or -1
% depending on whether goal is to be proved true or false
% (e.g. not Goal requires Goal be false in oreder to succeed).

solve(true,100,Rules,_).

solve(A,100,Rules,_) :-
    fact(A).

solve(A,-100,Rules,_) :-
    untrue(A).

solve(not(A),C,Rules,T) :-
    T2 is -1 * T,
    solve(A,C1,Rules,T2),
    C is -1 * C1.

solve((A,B),C,Rules,T) :-
    solve(A,C1,Rules,T),
    above_threshold(C1,T),
    solve(B,C2,Rules,T),
    above_threshold(C2,T),
    minimum(C1,C2,C).

solve(A,C,Rules,T) :-
    rule((A :- B),C1),
    solve(B,C2,[rule(A,B,C1)|Rules],T),
    C is (C1 * C2) / 100,
    above_threshold(C,T).

solve(A,C,Rules,T) :-
    rule((A), C),
    above_threshold(C,T).

solve(A,C,Rules,T) :-
    askable(A),
    not(known(A)),
    ask(A,Answer),
    respond(Answer,A,C,Rules).

% respond( Answer, Query, CF, Rule_stack).
% respond will process Answer (yes, no, how, why, help).
% asserting to working memory (yes or no)
% displaying current rule from rulestack (why)
% showing proof trace of a goal (how(Goal)
% displaying help (help).
% Invalid responses are detected and the query is repeated.

respond(Bad_answer,A,C,Rules) :-
    not(member(Bad_answer,[help, yes,no,why,how(_)])),
    write('answer must be either help, (y)es, (n)o, (h)ow(X), (w)hy'),nl,nl,
    ask(A,Answer),
    respond(Answer,A,C,Rules).

respond(yes,A,100,_) :-
    assert(fact(A)).

respond(no,A,-100,_) :-
    assert(untrue(A)).

respond(why,A,C,[Rule|Rules]) :-
    display_rule(Rule),
    ask(A,Answer),
    respond(Answer,A,C,Rules).

respond(why,A,C,[]) :-
    write('Back to goal, no more explanation  possible'),nl,nl,
    ask(A,Answer),
    respond(Answer,A,C,[]).

respond(how(Goal),A,C,Rules) :-
    respond_how(Goal),
    ask(A,Answer),
    respond(Answer,A,C,Rules).

respond(help,A,C,Rules) :-
    print_help,
    ask(A,Answer),
    respond(Answer,A,C,Rules).

% ask(Query, Answer)
% Writes Query and reads the Answer.  Abbreviations (y, n, h, w) are
% trnslated to appropriate command be filter_abbreviations

ask(Query,Answer) :-
    display_query(Query),
    read(A),
    filter_abbreviations(A,Answer),!.

% filter_abbreviations( Answer, Command)
% filter_abbreviations will expand Answer into Command.  If
% Answer is not a known abbreviation, then Command = Answer.

filter_abbreviations(y,yes).
filter_abbreviations(n,no).
filter_abbreviations(w,why).
filter_abbreviations(h,help).
filter_abbreviations(h(X),how(X)).
filter_abbreviations(X,X).

% known(Goal)
% Succeeds if Goal is known to be either true or untrue.

known(Goal) :- fact(Goal).
known(Goal) :- untrue(Goal).

% ask_for_trace(Goal).
% Invoked at the end of a consultation, ask_for_trace asks the user if
% they would like a trace of the reasoning to a goal.

ask_for_trace(Goal) :-
    write('Trace of reasoning to goal ? '),
    read(Answer),nl,
    show_trace(Answer,Goal),!.

% show_trace(Answer,Goal)
% If Answer is ``yes'' or ``y,'' show trace will display  a trace
% of Goal, as in a ``how'' query.  Otherwise, it succeeds, doing nothing.

show_trace(yes,Goal) :- respond_how(Goal).

show_trace(y,Goal) :- respond_how(Goal).

show_trace(_,_).

% print_help
% Prints a help screen.

print_help :-
    write('Exshell allows the following responses to queries:'),nl,nl,
    write('   yes - query is known to be true.'),nl,
    write('   no - query is false.'),nl,
    write('   why - displays rule currently under consideration.'),nl,
    write('   how(X) - if X has been inferred, displays trace of reasoning.'),nl,
    write('   help - prints this message.'),nl,
    write('   Your response may be abbreviated to the first letter and must end with a period (.).'),nl.

% display_query(Goal)
% Shows Goal to user in the form of a query.

display_query(Goal) :-
    write(Goal),
    write('? ').

% display_rule(rule(Head, Premise, CF))
% prints rule in IF...THEN form.

display_rule(rule(Head,Premise,CF)) :-
    write('IF       '),
    write_conjunction(Premise),
    write('THEN     '),
    write(Head),nl,
    write('CF   '),write(CF),
    nl,nl.

% write_conjunction(A)
% write_conjunction will print the components of a rule premise.  If any
% are known to be true, they are so marked.

write_conjunction((A,B)) :-
    write(A), flag_if_known(A),!, nl,
    write('     AND '),
    write_conjunction(B).

write_conjunction(A) :- write(A),flag_if_known(A),!, nl.

% flag_if_known(Goal).
% Called by write_conjunction, if Goal follows from current state
% of working memory, prints an indication, with CF.

flag_if_known(Goal) :-
    build_proof(Goal,C,_,1),
    write('     ***Known, Certainty = '),write(C).

flag_if_known(A).

% Predicates concerned with how queries.

% respond_how(Goal).
% calls build_proof to determine if goal follows from current state of working
% memory.  If it does, prints a trace of reasoning, if not, so indicates.

respond_how(Goal) :-
    build_proof(Goal,C,Proof,1),
    interpret(Proof),nl,!.

respond_how(Goal) :-
    build_proof(Goal,C,Proof,-1),
    interpret(Proof),nl,!.

respond_how(Goal) :-
    write('Goal does not follow at this stage of consultation.'),nl.

% build_proof(Goal, CF, Proof, Cutoff_context).
% Attempts to prove Goal, placing a trace of the proof in Proof.
% Functins the same as solve, except it does not ask for unknown information.
% Thus, it only proves goals that follow from the rule base and the current
% contents of working memory.

build_proof(true,100,(true,100),_).

build_proof(Goal, 100, (Goal :- given,100),_) :- fact(Goal).

build_proof(Goal, -100, (Goal :- given,-100),_) :- untrue(Goal).

build_proof(not(Goal), C, (not(Proof),C),T) :-
    T2 is -1 * T,
    build_proof(Goal,C1,Proof,T2),
    C is -1 * C1.

build_proof((A,B),C,(ProofA, ProofB),T) :-
    build_proof(A,C1,ProofA,T),
    above_threshold(C1,T),
    build_proof(B,C2,ProofB,T),
    above_threshold(C2,T),
    minimum(C1,C2,C).

build_proof(A, C, (A :- Proof,C),T) :-
    rule((A :- B),C1),
    build_proof(B, C2, Proof,T),
    C is (C1 * C2) / 100,
    above_threshold(C,T).

build_proof(A, C, (A :- true,C),T) :-
    rule((A),C),
    above_threshold(C,T).

% interpret(Proof).
% Interprets a Proof as constructed by build_proof,
% printing a trace for the user.

interpret((Proof1,Proof2)) :-
    interpret(Proof1),interpret(Proof2).

interpret((Goal :- given,C)):-
    write(Goal),
    write(' was given. CF = '), write(C),nl,nl.

interpret((not(Proof), C)) :-
    extract_body(Proof,Goal),
    write('not '),
    write(Goal),
    write(' CF = '), write(C),nl,nl,
    interpret(Proof).

interpret((Goal :- true,C)) :-
    write(Goal),
        write(' is a fact, CF = '),write(C),nl.

interpret(Proof) :-
    is_rule(Proof,Head,Body,Proof1,C),
    nl,write(Head),write(' CF = '),
    write(C), nl,write('was proved using the rule'),nl,nl,
    rule((Head :- Body),CF),
    display_rule(rule(Head, Body,CF)), nl,
    interpret(Proof1).

% isrule(Proof,Goal,Body,Proof,CF)
% If Proof is of the form Goal :- Proof, extracts
% rule Body from Proof.

is_rule((Goal :- Proof,C),Goal, Body, Proof,C) :-
    not(member(Proof, [true,given])),
    extract_body(Proof,Body).

% extract_body(Proof).
% extracts the body of the top level rule from Proof.

extract_body((not(Proof), C), (not(Body))) :-
    extract_body(Proof,Body).

extract_body((Proof1,Proof2),(Body1,Body2)) :-
    !,extract_body(Proof1,Body1),
    extract_body(Proof2,Body2).

extract_body((Goal :- Proof,C),Goal).

% Utility Predicates.

retractm(X) :- retract(X), fail.
retractm(X) :- retract((X:-Y)), fail.
retractm(X).

member(X,[X|_]).
member(X,[_|T]) :- member(X,T).

minimum(X,Y,X) :- X =< Y.
minimum(X,Y,Y) :- Y < X.

above_threshold(X,1) :- X >= 20.
above_threshold(X,-1) :- X =< -20.


%%%%%%%%%%%%%%%%%%%%%%%%%
%%%                   %%%
%%%  KNOWLEDGE BASES  %%%
%%%                   %%%
%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% GYM-TRAINING DIAGNOSIS KB %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% --- 1. TOP-LEVEL GOAL ---
% RUN: ?- solve(training_advice(Advice))
rule((training_advice(Advice) :-
        training_issue(Issue),
        fix_issue(Issue,Advice)), 100).


% --- 2. TRAINING-ISSUE DIAGNOSIS -
% Overtraining / non-functional over-reaching
rule((training_issue(overtraining) :-
        root_cause(recovery_issue),
        performance_dropping,
        soreness_duration_long),  85).
% Volume is simply too high (but not yet full overtraining)
rule((training_issue(volume_too_high) :-
        root_cause(volume_issue),
        rpe_high,
        soreness_duration_long),  80).
% Intensity/load too high (too many sets at RPE 9-10)
rule((training_issue(intensity_too_high) :-
        root_cause(intensity_issue),
        rpe_high,
        injury_signs),            75).
% General under-recovery without outright OT symptoms
rule((training_issue(under_recovery) :-
        root_cause(recovery_issue),
        motivation_low),          70).


% --- 3. ROOT-CAUSE REASONING ---
rule((root_cause(recovery_issue) :-
        sleep_poor,
        caloric_intake_low),      90).
rule((root_cause(volume_issue) :-
        volume_per_muscle_high,
        soreness_duration_long),  80).
rule((root_cause(intensity_issue) :-
        rpe_high,
        motivation_low),          70).


% --- 4. PRESCRIPTIVE FIXES  ---
rule(fix_issue(overtraining,
        'Take a deload week: cut volume ~50%, keep loads light, focus on sleep & nutrition'), 100).
rule(fix_issue(volume_too_high,
        'Reduce weekly set volume 20-30% and re-assess recovery after 1-2 weeks'),            100).
rule(fix_issue(intensity_too_high,
        'Lower working weights 5-10%, stay 1-2 reps-in-reserve (RIR) for most sets'),         100).
rule(fix_issue(under_recovery,
        'Prioritise 8-9 h sleep and increase daily calories by ~10% (esp. protein & carbs)'), 100).
rule(fix_issue(recovery_issue,
        'Improve sleep hygiene, manage stress, and increase calorie intake'),                 100).


% --- 5. ASKABLE FACTS (what the shell may ask the user) ---
askable(performance_dropping).    % “Have your lifts/regression plateaued or declined lately?”
askable(soreness_duration_long).  % “Does soreness last > 3 days in the same muscle?”
askable(motivation_low).          % “Is your motivation to train noticeably reduced?”
askable(sleep_poor).              % n“Are you sleeping < 7 h/night or waking unrefreshed?”
askable(caloric_intake_low).      % “Have you been eating below maintenance / in a deficit?”
askable(rpe_high).                % “Are most sets ending at RPE 9-10 (0-1 RIR) lately?”
askable(volume_per_muscle_high).  % “Are you doing > 20 hard sets / muscle / week?”
askable(injury_signs).            % “Do you feel joint/tendon niggles worsening?”

