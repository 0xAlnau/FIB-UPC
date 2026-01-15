%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Notació:
%%   * "donat N" significa que l'argument N estarà instanciat inicialmente.
%%   * "ha de ser capaç de generar totes les respostes possibles" significa que
%%     si hi ha backtracking ha de poder generar la següent resposta, com el
%%     member(E,L) que per una llista L "donada" pot generar tots els elements E.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En LI adapterem la "Notation of Predicate Descriptions" de SWI-Prolog per
%% descriure els predicats, prefixant cada argument amb un d'aquests 3 símbols:
%%   '+' quan l'argument ha d'estar necessàriament instanciat (no pot ser una
%%       variable sense instanciar). Pot ser ground (f(a) o 34)" o no (X+1 o g(a,Y)).
%%       Quan parlem de "donada L", llavors especficarem +L en la *descripció*.
%%       Per exemple, l'argument de +L del predicat esta_ordenada(+L).
%%   '-' quan l'argument ha de ser necessàriament una variable que quedarà
%%       instanciada, al satisfer-se el predicat, amb un cert terme que podem
%%       veure com un "resultat".
%%       Per exemple, l'argument -F en el predicat fact(+N,-F) que per un N donat,
%%       se satisfà fent que F sigui el valor N!.
%%   '?' quan s'accepta que l'argument pugui estar instanciat o no.
%%       Es tracta dels casos en que es diu "ha de poder generar la S i també
%%       comprovar una S donada". Llavors especificarem ?S en la *descripció*.
%%       Per exemple, l'argument ?S de suma(+L,?S).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En aquests exercicis feu servir els predicats propis de SWI Prolog:
%%   * member(E,L)         en lloc de  pert(E,L)
%%   * append(L1,L2,L3)    en lloc de  conc(L1,L2,L3)
%%   * select(E,L,R)       en lloc de  pert_amb_resta(E,L,R)
%%   * permutation(L,P)    en lloc de  permutacio(L,P)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



% PROB. A =========================================================
% Escriu un predicat
% prod(+L,?P)  que signifiqui: P és el producte dels
% elements de la llista de enters donada L. Ha de poder generar la
% P i també comprovar una P donada


prod([], 1). %quan s'acaba la llista tornem multiplicant per 1
prod([X | L], P) :- prod(L, P1), P is P1 * X.



% PROB. B =========================================================
% Escriu un predicat
% pescalar(+L1,+L2,?P) que signifiqui: P és el producte escalar dels
% vectors L1 i L2, on els vectors es representen com llistes
% d'enters. El predicat ha de fallar si els dos vectors
% tenen longituds diferents.
% ex: (3,5) * (5,0) = 15 + 0 = 15


pescalar([], [], 0).
pescalar([X1 | L1], [X2 | L2], P) :- pescalar(L1 ,L2, P1) , P is X1*X2 + P1.


% PROB. C =========================================================
% Representant conjunts com llistes sense repeticions, escriu
% predicats per les operacions d'intersecció i unió de conjunts donats

% interseccio(+L1,+L2,?L3)
% ex: [1,2,3,4,5] [1,3,5] -> [1,3,5]


interseccio([], _, []).
interseccio([X | L1], L2, [X | L3]) :- member(X,L2), !, interseccio(L1, L2, L3). % X es membre de L2, afegim
interseccio([_ | L1], L2, L3) :- interseccio(L1, L2, L3). % X no es membre de L2, no fem res seguim


% unio(+L1,+L2,?L3)


unio([], L, L).
unio([X | L1], L2, L3) :- member(X, L2), !, unio(L1, L2, L3). % X pertany a L2 i no unim
unio([X | L1], L2, [X | L3]) :- unio(L1, L2, L3). % X no pertany a L2 i unim



% PROB. D =========================================================
% Usant append/3, escriu un predicat per calcular l'últim 
% element d'una llista donada, i un altre per calcular la llista
% inversa d'una llista donada.

% ultim(+L,?E)
% ex: [1,2,3,4] -> 4
ultim(L, X) :- append(_, [X], L). % element x és l'últim de la llista L si L es la concatenació d'alguna llista amb la llista [x] (4 únic que esta a cada llista de L pel final)


% inversa(+L1,?L2)
% ex: [1,2,3,4] -> [4,3,2,1]
inversa([], []).
inversa(L, [X | P]) :- append(L2, [X], L), inversa(L2, P).


% PROB. E =========================================================
% Escriu un predicat
% fib(+N,?F) que signifiqui: F és l'N-éssim nombre de Fibonacci
% per a la N donada. Aquests nombres es defineixen així:
% fib(1) = 1, fib(2) = 1, i si N > 2 llavors
% fib(N) = fib(N-1) + fib(N-2)
fib(1, 1) :- !.
fib(2, 1) :- !.
fib(N, F) :- N1 is N-1, N2 is N-2, fib(N1, F1), fib(N2, F2), F is F1 + F2.


% PROB. F =========================================================
% Escriu un predicat
% dados(+P,+N,-L) que signifiqui: la llista L expressa una forma de
% sumar P punts llançant N daus. Per exemple: si P és 5, i
% N és 2, una solució seria [1,4] (noteu que la longitud de L és N.
% Tant P com N venen instanciats. El predicat deu ser capaç de
% generar totes les solucions possibles,
dados(0,0,[]).
dados(P,N,[X|L]) :- N>0, member(X,[1,2,3,4,5,6]), Q is P-X, M is N-1, dados(Q,M,L).


% PROB. G =========================================================
% Escriu un predicat
% suma_la_resta(+L) que, donada una llista d'enters L, es satisfà si
% existeix algun element en L que és igual a la suma de la resta
% d'elements de L, i que altrament falla.
% Escriu abans un predicat
% suma(+L,?S) que, donada una llista d'enters L, se satisfà si S
% és la suma dels elements d'L.

% suma(+L,?S)
suma([], 0).
suma([X | L], S) :- suma(L, S2), S is S2 + X.


% suma_la_resta(+L)
%suma_la_resta([]) :- suma([], 0).
suma_la_resta(L) :- append(L1, [X|_], L), suma(L1,X), !.




% PROB. H =========================================================
% Escriu un predicat
% card(+L) que, donada una llista d'enters L, escriba la llista
% que, para cada element d'L, diu quantes vegades surt aquest
% element en L.
% Per exemple, si fem la consulta
% card( [1,2,1,5,1,3,3,7] )  l'intèrpret escriurà:
% [[1,3],[2,1],[5,1],[3,2],[7,1]].
card([],[]).
card([X | L], [[X,N1] | S2] ) :- card(L,S), select([X,N],S,S2),!,N1 is N+1.
card([X | L], [[X,1] | S] ) :- card(L,S).

card(L) :- card(L,S), write(S).






% PROB. I ========================================================
% Escriu un predicat
% esta_ordenada(+L) que signifiqui: la llista L de nombres enters
% està ordenada de menor a major.
% Per exemple, a la consulta:
% ?- esta_ordenada([3,45,67,83]).
% l'intèrpret respon yes, i a la consulta:
% ?- esta_ordenada([3,67,45]).
% respon no.

esta_ordenada([]).
esta_ordenada([_]) :- !.
esta_ordenada([X, Y | L]) :- X =< Y , esta_ordenada([Y | L]).






% PROB. J ========================================================
% Escriu un predicat
% palíndroms(+L) que, donada una llista de lletres L escrigui
% totes les permutacions dels seus elements que siguin palíndroms
% (capicues). Per exemple, amb la consulta palindrom([a,a,c,c])
% s'escriu [a,c,c,a] i [c,a,a,c]
% (possiblement diverses vegades, no cal que eviteu les repeticions).

palindroms(L) :- permutation(L,P), es_palindrom(P), write(P), nl, fail.
palindroms(_).

es_palindrom([]).
es_palindrom([_]) :- !. % tall
es_palindrom([X|L]) :- append(L1,[X],L), es_palindrom(L1).



% PROB. K ========================================================
% Volem obtenir en Prolog un predicat
% dom(+L) que, donada una llista L de fitxes de dominó (en el format
% indicat abaix), escrigui una cadena de dominófent servir *totes*
% les fitxes de L, o escrigui "no hi ha cadena" si no és possible.
% Per exemple,
% ?- dom( [ f(3,4), f(2,3), f(1,6), f(2,2), f(4,2), f(2,1) ] ).
% escriu la cadena correcta:
% [ f(2,3), f(3,4), f(4,2), f(2,2), f(2,1), f(1,6) ].
%
% També podem "girar" alguna fitxa como f(N,M), reemplaçant-la
% per f(M,N). Així, per:
% ?- dom( [ f(4,3), f(2,3), f(1,6), f(2,2), f(2,4), f(2,1) ] ).
% només hi ha cadena si es gira alguna fitxa (per exemple, hi ha
% mateixa cadena d'abans).
%
% El següent programa Prolog encara no té implementat els possibles
% girs de fitxes, ni té implementat el predicat ok(P), que
% significa: P és una cadena de dominó correcta (tal qual,
% sense necessitat de girar cap fitxa):

p([],[]).
p(L,[X|P]) :- select(X,L,R), p(R,P).

dom(L) :- p(L,P), ok(P), write(P), nl.
dom(_) :- write('no hi ha cadena'), nl.

% a) Escriu el predicat ok(+P) que falta.






% b) Estén el predicat p/2 per a que el programa també pugui
%    fer cadenes girant alguna de les fitxes de l'entrada.







% PROB. L ========================================================
% Write in Prolog a predicate aplanada(+L,?F) that ``flattens''
% (cat.: ``aplana'') the list F as in the example:
% ?- aplanada( [a,b,[c,[d],e,[]],f,[g,h]], F ).
% F = [a,b,c,d,e,f,g,h]

aplanada([], []).
aplanada([X | E], S) :- append(X, S, S), aplanada(E, S2), append(S, S2, S), write(S).


% PROB. M ========================================================
% Consider two groups of 10 people each. In the first group,
% as expected, the percentage of people with lung cancer among smokers
% is higher than among non-smokers.
% In the second group, the same is the case.
% But if we consider the 20 people of the two groups together, then
% the situation is the opposite: the proportion of people with
% lung cancer is higher among non-smokers than among smokers!
% Can this be true? Write a little Prolog program to find it out.

%% Descomenteu i completeu les linies de codi que veieu a continuació:
%% main :-
%%     between(0,3,SC1),    % SC1:   "no.    smokers with    cancer group 1"
%%     between(0,3,SNC1),   % SNC1:  "no.    smokers with no cancer group 1"
%%     between(0,3,NSC1),   % NSC1:  "no. no smokers with    cancer group 1"
%%     between(0,3,NSNC1),  % NSNC1: "no. no smokers with no cancer group 1"
%%     10 is SC1+SNC1+NSC1+NSNC1,  
%%     ...
