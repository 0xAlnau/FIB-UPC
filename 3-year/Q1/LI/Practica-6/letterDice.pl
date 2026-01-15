:- use_module(library(clpfd)).

%% A (6-sided) "letter dice" has on each side a different letter.
%% Find four of them, with the 24 letters abcdefghijklmnoprstuvwxy such
%% that you can make all the following words: bake, onyx, echo, oval,
%% gird, smug, jump, torn, luck, viny, lush, wrap, fame.

% Some helpful predicates:

word( [b,a,k,e] ).
word( [o,n,y,x] ).
word( [e,c,h,o] ).
word( [o,v,a,l] ).
word( [g,i,r,d] ).
word( [s,m,u,g] ).
word( [j,u,m,p] ).
word( [t,o,r,n] ).
word( [l,u,c,k] ).
word( [v,i,n,y] ).
word( [l,u,s,h] ).
word( [w,r,a,p] ).
word( [f,a,m,e] ).

% num(?X, ?N)   "La lletra X és a la posició N de la llista"
num(X, N) :- nth1( N, [a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,r,s,t,u,v,w,x,y], X ).


main :-
%1: Variables i dominis:
    length(D1, 6),
    length(D2, 6),
    length(D3, 6),
    length(D4, 6),

    D1 ins 1..24, chain(D1, #=<), %ordenem per mes eficiencia
    D2 ins 1..24, chain(D2, #=<),
    D3 ins 1..24, chain(D3, #=<),
    D4 ins 1..24, chain(D4, #=<),

%2: Constraints:
%fer llista de parells de lletres que no poden apareixer en el mateix dau, usar predicats #\=, #\/, #/\
    append([D1,D2,D3,D4], TotesLletres), %volem veure que totes son diferents
    all_different(TotesLletres),

    findall(W, word(W), Words), %agafem totes les paraules
    check_words(Words,[D1,D2,D3,D4]), %comprovem cada dau aporta 1 lletra a cada paraula

%3: Labeling:
    label(TotesLletres),

%4: Escrivim el resultat:
    writeN(D1), nl,
    writeN(D2), nl,
    writeN(D3), nl,
    writeN(D4), nl, halt.
    
writeN(D) :- findall(X, (member(N,D),num(X,N)), L), write(L), nl, !.

%es pot fer A=B o A=C
% A #= B
% # \/
% A #= C

%Constraints

%un bucle 'for' es pot fer de forma recursiva, paraula per paraula

check_words([], _).
check_words([W | ResWords],Daus) :-
    translate(W, WNums), %traduim a numeros la paraula
    can_be_formed(WNums, Daus), %es pot formar la paraula amb els daus
    check_words(ResWords, Daus). %seguim amb la resta

translate([], []).
translate([Lletra | Resta], [N | NewWord]) :-
    num(Lletra, N), %tradueix el cap
    translate(Resta, NewWord). %tradueix la resta

can_be_formed([], _).
can_be_formed([Num | RestNums], Daus) :-
    select(Dau, Daus, RestDaus),
    member(Num, Dau),
    can_be_formed(RestNums, RestDaus).



