
symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Your hometown is building a new boulevard and it requires some trees.
%% There are three types of trees required:
%%  'shadow'    (s) are shadow trees with big leafs for summer, 
%%  'flowering' (f) are flowering trees that are beautiful in spring and have a good smell,
%%  'evergreen' (e) are evergreen trees so that the place will look green in winter as well.
%% We call a tree nursery and they give us a list of available trees with 3 parameters:
%% [type, size, cost] with the tree type, sizes of tree (small, medium or large),
%% and the cost of the tree, an integer.
%% Small trees cover 2m (2 meters), medium trees cover 4m, and large trees cover 6m
%% of the boulevard.
%% A tree located at "start place" P, and size S, covers the places P,P+1,...,P+S-1.
%% No place in the boulevard can be covered by more than one tree.
%% Additionally, no tree can cover outside the boulevard's boundaries, and we want trees
%% to cover at least 90% of the boulevard.
%% Every type of tree (shadow, flowering, evergreen) must be present in the boulevard.
%% We don't want three adjacent trees of the same type. Adjacent means
%% "without extra space between them", so they cover a list of consecutive places. Look at
%% the 'evergreen' trees F, G, and H, in the solution below.
%%
%% Given the boulevard length, the sequence of available trees, and a maximal cost,
%% find a solution for the boulevard.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% Begin INPUT in example boulevardExampleA.pl %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% % boulevardLength(Length).
%% boulevardLength(20).
%% 
%% % available(TreeId, [Type, Size, Cost]). 
%% available('A', [shadow,    large,  10]). 
%% available('B', [flowering, large,  11]). 
%% available('C', [flowering, small,   2]). 
%% available('D', [shadow,    medium,  5]).
%% available('E', [evergreen, large,  10]).
%% available('F', [evergreen, large,   8]). 
%% available('G', [evergreen, medium,  4]). 
%% available('H', [evergreen, small,   1]). 
%% available('I', [shadow,    small,   1]). 
%% available('J', [flowering, medium,  5]).
%%
%% % maximumCost(MaximumTotalCost).
%% maximumCost(20).

%%%%%%% End INPUT in example boulevardExampleA.pl  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Example of OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%%          1         2
%% 12345678901234567890
%%  F      G   H I J   
%% .eeeeee.eeeeeessffff
%%
%% ==== Detailed information: ====
%%
%% tree F: type=evergreen size=6 placed/start=[2]  end=[7]  cost=8
%% tree G: type=evergreen size=4 placed/start=[9]  end=[12] cost=4
%% tree H: type=evergreen size=2 placed/start=[13] end=[14] cost=1
%% tree I: type=shadow    size=2 placed/start=[15] end=[16] cost=1
%% tree J: type=flowering size=4 placed/start=[17] end=[20] cost=5
%% trees [A,B,C,D,E]: not used
%%
%% total cost: 19
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% IMPORTANT: Due to the uncovered place 8, the 'evergreen' trees F, G, and H
%%            are NOT considered to be "three adjacent trees of the same type".
%%
%% NOTE on how the solution is shown:
%%      the character '!' at some place means that there are *more than one tree*
%%      covering that place. If these characters are present, that solution is not valid.


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

boulevardPlace(P) :- boulevardLength(L), between(1,L,P).

tree(T)          :- available(T,_).
treeType(T,Type) :- available(T,[Type,_,_]).
treeSize(T,2)    :- available(T,[_,small,_]).
treeSize(T,4)    :- available(T,[_,medium,_]).
treeSize(T,6)    :- available(T,[_,large,_]).
treeCost(T,Cost) :- available(T,[_,_,Cost]).
threeDifferentTreesOfSameType(T1,T2,T3) :- treeType(T1,Type), treeType(T2,Type), T1 \= T2,
                                           treeType(T3,Type), T1 \= T3, T2 \= T3.
minimumCoveredPlaces(MinPlaces) :- boulevardLength(L), MinPlaces is ceil(0.9*L).

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. Declare SAT variables to be used: =================================================

% SAT variable treeStart(T,P) means "tree T starts at place P (P is the leftmost position it covers)"
satVariable( treeStart(T,P) ) :- tree(T), boulevardPlace(P).
% SAT variable covered(P)     means "place P is covered by some tree"
satVariable( covered(P)     ) :- boulevardPlace(P).
% SAT variable treeUsed(T)    means "tree T is in some place of the boulevard"
satVariable( treeUsed(T)    ) :- tree(T).


%%%%%%%  2. Clause generation for the SAT solver: =============================================

writeClauses :-
    % Each tree can be placed/starts at most once in the boulevard:
    eachTreeAtMostOneStartPlace,
    % Each place in the boulevard at most "starts" one tree:
    eachStartPlaceAtMostOneTree,
    % "No tree can cover outside the boulevard's boundaries":
    noTreeCoverOutsideBoundaries,
    % "No place in the boulevard can be covered by more than one tree":
    leaveEnoughDistanceBetweenDifferentStarts,
    % "We don't want three adjacent trees of the same type":
    noThreeAdjacentTreesOfSameType,
    % Relate "covered" SAT var with "treeStart" SAT var:
    defineCoveredSATvar,
    % 90% of places in the boulevard have to be covered:
    ninetyPercentIsCovered,
    % Relate "treeUsed" SAT var with "treeStart" SAT var:
    defineTreeUsedSATvar,
    % "Every type of tree (shadow, flowering, evergreen) must be present in the boulevard":
    everyTypeOfTreeIsPresent,
    % The cost of the solution is limited:
    costMustBeLessOrEqualMaxCost,
    true, !.
writeClauses:- told, nl, write('writeClauses failed!'), nl,nl, halt.

%% Each tree can be placed/starts at most once in the boulevard:
eachTreeAtMostOneStartPlace :-
    tree(T),
    findall( treeStart(T,P), boulevardPlace(P), Lits ),
    atMost(1,Lits),
    fail.
eachTreeAtMostOneStartPlace.

%% Each place in the boulevard at most "starts" one tree:
eachStartPlaceAtMostOneTree :-
    %% ...
    boulevardPlace(P), % per CADA punt P
    findall(treeStart(T,P), tree(T), Lits),
    atMost(1, Lits), % nomes un arbre en aquell lloc
    fail.
eachStartPlaceAtMostOneTree.

% "No tree can cover outside the boulevard's boundaries":
noTreeCoverOutsideBoundaries :-
    tree(T),
    treeSize(T, S),
    boulevardLength(L),
    boulevardPlace(P), %mira en quin punt em puc sortir
    P + S - 1 > L, % si des de punt p em surt malament
    writeOneClause( [-treeStart(T,P)] ),
    fail.
noTreeCoverOutsideBoundaries.

%% "No place in the boulevard can be covered by more than one tree":
leaveEnoughDistanceBetweenDifferentStarts :-
    %% ...
    boulevardPlace(P), % per cada punt P, nomes un arbre el pot cobrir
    findall( treeStart(T,Pt), (tree(T), treeSize(T,S), S1 is S-1, between(0,S1,DP), Pt is P-DP, boulevardPlace(Pt)), Lits ), % troba literals on es cubreixi el punt P
    atMost(1, Lits), % Com a màxim un d'aquests literals pot ser cert
    fail.
leaveEnoughDistanceBetweenDifferentStarts.

%% "We don't want three adjacent trees of the same type":
noThreeAdjacentTreesOfSameType :-
    %% ...
    threeDifferentTreesOfSameType(T1, T2, T3), %busca tres arbres mateix tipus
    treeSize(T1, S1),
    treeSize(T2, S2),
    treeSize(T3, S3),
    boulevardLength(L),

    boulevardPlace(P1), %mirem posicions per t1
    P1 + S1 - 1 =< L, % que capiga

    % calcula on haurien d'anar T2 i T3 per ser adjacents
    P2 is P1 + S1, % T2 comença just on acaba T1
    P2 =< L, % Assegura't que P2 és dins el bulevard
    P2 + S2 - 1 =< L, % Assegura't que T2 hi cap

    P3 is P2 + S2, % T3 comença just on acaba T2
    P3 =< L, % Assegura't que P3 és dins el bulevard
    P3 + S3 - 1 =< L, % Assegura't que T3 hi cap

    writeOneClause( [-treeStart(T1,P1), -treeStart(T2,P2), -treeStart(T3,P3)] ), % si son continus que no puguin coincidir
    fail.
noThreeAdjacentTreesOfSameType.

%% Relate "covered" SAT var with "treeStart" SAT var:
defineCoveredSATvar :-
    boulevardPlace(P),
    findall( treeStart(T,Pt), (treeSize(T,S), S1 is S-1, between(0,S1,DP), Pt is P-DP, boulevardPlace(Pt)), Lits ),    
    expressOr(covered(P), Lits),
    fail.
defineCoveredSATvar.

%% 90% of places in the boulevard have to be covered:
ninetyPercentIsCovered :-
    %% ...
    minimumCoveredPlaces(CP),
    findall(covered(P), boulevardPlace(P), Lits),
    atLeast(CP, Lits),
    fail.
ninetyPercentIsCovered.

%% Relate "treeUsed" SAT var with "treeStart" SAT var:
defineTreeUsedSATvar :-
    tree(T),
    %% ...
    findall(treeStart(T,P), boulevardPlace(P), Lits),
    expressOr(treeUsed(T), Lits),
    fail.
defineTreeUsedSATvar.

%% "Every type of tree (shadow,flowering,evergreen) must be present in the boulevard":
everyTypeOfTreeIsPresent :-
    %% ...
    findall(treeUsed(T), treeType(T, 'shadow'), Lits1),
    atLeast(1, Lits1),

    findall(treeUsed(T2), treeType(T2, 'flowering'), Lits2),
    atLeast(1, Lits2),

    findall(treeUsed(T3), treeType(T3, 'evergreen'), Lits3),
    atLeast(1, Lits3),

    fail.
everyTypeOfTreeIsPresent.

%% The cost of the solution is limited:
costMustBeLessOrEqualMaxCost :-
    maximumCost(MaxCost),
    findall([T,C], treeCost(T,C), LTC),
    minSubset(MaxCost, LTC, LTm),
    %% ...

    findall( -treeUsed(T), member(T, LTm), Lit), %agafem els arbres mínims que superen el cost
    writeOneClause(Lit), %diem que no els usi
    fail.
costMustBeLessOrEqualMaxCost.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% The predicates minSubset/3 and generateSubset/5 below are used in          %%
%% costMustBeLessOrEqualMaxCost. They are commented and entirely defined.     %%
%% They are used to generate MINIMAL subsets of trees whose sum of costs      %%
%% exceeds a given value.                                                     %%
%% For instance, one minimal subset that exceeds cost 30 in boulevardExampleA %%
%% above is ['A','B','D','F'], since 10+11+5+8 > 30 and the total cost of any %%
%% three of those trees is <= 30.                                             %%

% minSubset(+K1,+LTC,-LTm):
%   given an integer K1, and a list LTC of pairs [Tree,Cost], generate
%   a minimal subset of trees LTm s.t.
%     * the sum of costs of the trees in LTm > K1, and
%     * if a tree is removed from LTm the sum of costs of the remaining
%       trees is <= K1
minSubset(K1, LTC, LTm) :-
    findall(C, member([_,C], LTC), LC),
    max_list(LC,Max),
    K2 is K1+Max,
    generateSubset(K1, K2, LTC, LTm, LCm),
    sum_list(LCm, Sum),
    min_list(LCm, Min),
    Sum-Min =< K1.

% generateSubset(+K1,+K2,+LTC,-LTm,-LCm):
%   given two integers K1 and K2, and a list LTC of pairs [Tree,Cost] generate
%   a subset of trees LTm, and the list of corresponding costs LCm, s.t.
%   the sum of costs S satisfy K1 < S <= K2
generateSubset(K1, K2, [[T,C]|_], [T], [C]) :- C > K1, C =< K2.
generateSubset(K1, K2, [[T,C]|L], [T|LT], [C|LC]) :-
    K1P is K1 - C, K2P is K2 - C,
    generateSubset(K1P, K2P, L, LT, LC).
generateSubset(K1, K2, [_|L], LT, LC) :- 
    generateSubset(K1, K2, L, LT, LC).


%%%%%%%  3. DisplaySol: this predicate displays a given solution M: ===========================

%displaySol(M) :- write(M), nl, nl, fail.
displaySol(_) :- nl, boulevardLength(L), write('%% '), between(1,L,N), (0 is N mod 10 -> Q is N div 10, write(Q) ; write(' ')), fail.
displaySol(_) :- nl, write('%% '), boulevardLength(L), between(1,L,N), R is N mod 10, write(R), fail.
displaySol(M) :- nl, write('%% '), boulevardPlace(P), writeTreeAtPlace(P,M), fail.
displaySol(M) :- nl, write('%% '), boulevardPlace(P), writeTreeTypeAtPlace(P,M), fail.
displaySol(M) :- boulevardLength(L), L1 is L+1 , L5 is L+5, between(L1,L5,P),
                 writeTreeTypeAtPastEndPlace(P,M), fail.
displaySol(_).

write2(N) :- N < 10, !, write(' '), write(N).
write2(N) :- write(N).

writeTreeAtPlace(P,M) :-
    findall( T, member(treeStart(T,P),M), L),
    ( L = []  -> write(' ') ; ( L = [T1] -> write(T1) ; write('!') ) ).

writeTreeTypeAtPlace(P,M) :-
    findall( T, (member(treeStart(T,P1),M),P1=<P,treeSize(T,Size),P1+Size>P), L),
    ( L = [] -> write('.') ; ( L = [T1] -> treeType(T1,Type), writeType(Type) ; write('!') ) ).

writeTreeTypeAtPastEndPlace(P,M) :-
    findall( T, (member(treeStart(T,P1),M),treeSize(T,Size),P1+Size>P), L),
    ( L = [] -> write(' ') ; ( L = [T1] -> treeType(T1,Type), writeType(Type) ; write('!') ) ).

writeType(shadow)    :- write('s').
writeType(flowering) :- write('f').
writeType(evergreen) :- write('e').

displaySolDetails(_) :- nl, nl, write('==== Detailed information: ===='), fail.
displaySolDetails(M) :- nl, tree(T), findall(P, (boulevardPlace(P), member(treeStart(T,P),M)), L),
                        L \= [],
                        nl, write('tree '), write(T),
                        write(': type='), treeType(T,Type), write(Type),
                        write(' size='), treeSize(T,S), write(S),
                        write(' placed/start='), write(L),
                        findall(Pe, (member(P,L), Pe is P+S-1), Le),
                        write(' end='), write(Le),
                        write(' cost='), treeCost(T,C), write(C),
                        fail.
displaySolDetails(M) :- findall(T, (tree(T), findall(P, (boulevardPlace(P), member(treeStart(T,P),M)), L), L == []), LT),
                        LT \= [],
                        nl, write('trees '), write(LT), write(': not used'),
                        fail.
displaySolDetails(M) :- costOfThisSolution(M, Cost),
                        nl, nl, write('total cost: '), write(Cost), fail.
displaySolDetails(_).

%% Cost is the sum of the costs of the trees in the solution/model M.
%% This approach uses the SAT variables treeStart(T,P).
costOfThisSolution(M,Cost) :-
    findall( T:C, (tree(T),boulevardPlace(P),member(treeStart(T,P),M),treeCost(T,C)), TCs ),
    sort(TCs, TCs1),  % required if eachTreeAtMostOneStartPlace does not work properly
    findall( C, member(_:C, TCs1), Cs ),
    sum_list(Cs,Cost).

%% An alternative solution that uses the SAT variables treeUsed(T).
%% Every tree sums up only ONCE, even if erroneously placed multiple times.
%% Nevertheless, the SAT variable treeUsed(T) must be accurately related to treeStart(T,P).
%% costOfThisSolution(M, Cost) :-
%%     findall( C, (treeCost(T,C), member(treeUsed(T),M) ), Cs), 
%%     sum_list(Cs,Cost).


%%%%%%% =======================================================================================



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Everything below is given as a standard library, reusable for solving
%%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Cardinality constraints on arbitrary sets of literals Lits: ===========================

exactly(K,Lits) :- symbolicOutput(1), write( exactly(K,Lits) ), nl, !.
exactly(K,Lits) :- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits) :- symbolicOutput(1), write( atMost(K,Lits) ), nl, !.
atMost(K,Lits) :-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
      negateAll(Lits,NLits),
      K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeOneClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits) :- symbolicOutput(1), write( atLeast(K,Lits) ), nl, !.
atLeast(K,Lits) :-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
      length(Lits,N),
      K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeOneClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ) :- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate( -Var,  Var) :- !.
negate(  Var, -Var) :- !.

subsetOfSize(0,_,[]) :- !.
subsetOfSize(N,[X|L],[X|S]) :- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ) :-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%%% Express equivalence between a variable and a disjunction or conjunction of literals ===

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ) :- symbolicOutput(1), write( Var ), write(' <--> or('), write(Lits), write(')'), nl, !.
expressOr( Var, Lits ) :- member(Lit,Lits), negate(Lit,NLit), writeOneClause([ NLit, Var ]), fail.
expressOr( Var, Lits ) :- negate(Var,NVar), writeOneClause([ NVar | Lits ]),!.

%% expressOr(a,[x,y]) genera 3 clausulas (como en la Transformación de Tseitin):
%% a == x v y
%% x -> a       -x v a
%% y -> a       -y v a
%% a -> x v y   -a v x v y

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits) :- symbolicOutput(1), write( Var ), write(' <--> and('), write(Lits), write(')'), nl, !.
expressAnd( Var, Lits) :- member(Lit,Lits), negate(Var,NVar), writeOneClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits) :- findall(NLit, (member(Lit,Lits), negate(Lit,NLit)), NLits), writeOneClause([ Var | NLits]), !.


%%%%%%% main: =================================================================================

main :- current_prolog_flag(os_argv, Argv),
        nth0(1, Argv, InputFile),
        main(InputFile), !.
main :-  write('Usage: $ ./<executable> <example>          or ?- main(<example>).'), nl, halt.

main(InputFile) :-
        symbolicOutput(1), !,
        consult(InputFile),
        writeClauses, halt.   % print the clauses in symbolic form and halt Prolog
main(InputFile):-
        consult(InputFile),
        initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
        tell(header),  writeHeader, told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Calling solver....'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result),!.

treatResult(20) :- write('Unsatisfiable'), nl, halt.
treatResult(10) :- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), displaySolDetails(M), nl,nl,halt.
treatResult( _) :- write('cnf input error. Wrote anything strange in your cnf?'), nl,nl, halt.


initClauseGeneration:-  %initialize all info about variables and clauses:
        retractall(numClauses(   _)),
        retractall(numVars(      _)),
        retractall(varNumber(_,_,_)),
        assert(numClauses( 0 )),
        assert(numVars(    0 )),     !.

writeOneClause([]) :- symbolicOutput(1),!, nl.
writeOneClause([]) :- countClause, write(0), nl.
writeOneClause([Lit|C]) :- w(Lit), writeOneClause(C),!.
w(-Var) :- symbolicOutput(1), satVariable(Var), write(-Var), write(' '),!.
w( Var) :- symbolicOutput(1), satVariable(Var), write( Var), write(' '),!.
w(-Var) :- satVariable(Var),  var2num(Var,N),   write(-), write(N), write(' '),!.
w( Var) :- satVariable(Var),  var2num(Var,N),             write(N), write(' '),!.
w( Lit) :- told, write('ERROR: generating clause with undeclared variable in literal '), write(Lit), nl,nl, halt.


% given the symbolic variable V, find its variable number N in the SAT solver:
:- dynamic(varNumber / 3).
var2num(V,N) :- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N) :- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N) :- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader :- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause :-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N) :- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M) :- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]) :- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord( -1,_) :-!, fail. %end of file
readWord(C, []) :- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]) :- get_code(Char1), readWord(Char1,W), !.

%%%%%%% =======================================================================================
