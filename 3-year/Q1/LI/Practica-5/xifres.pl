subcjt([],[]). %subcjt(L,S) es: "S es un subconjunto de L".
subcjt([X|C],[X|S]):-subcjt(C,S).
subcjt([_|C],S):-subcjt(C,S).

xifres(L,N):-
    D is 0,
    xifres1(L,N,D).

xifres1(L,N,D):-
    length(L,MaxLen),
    between(1, MaxLen, K), % K indica n valors al subcjt

    Menys is N - D,
    Mes is N + D,
    write("probem valor:"+N+" a distancia:"+D), nl,
    xifres3(L,Menys,K),
    xifres3(L,Mes,K),
    fail.

xifres1(L,N,D):-
    D1 is D + 1,
    xifres1(L,N,D1).

xifres3(L,N,K):-
    subcjt(L,S),
    length(S,K), %forçar mides dels subcjt
    permutation(S,P),
    expresio(P,E),
    N is E,
    write(E), nl, fail.

xifres3(_,_,_).

expresio([X],X).

expresio(L,E1+E2):-
    append(L1,L2,L),
    L1\=[],L2\=[],
    expresio(L1,E1),
    expresio(L2,E2).

expresio(L,E1-E2):-
    append(L1,L2,L),
    L1\=[],L2\=[],
    expresio(L1,E1),
    expresio(L2,E2).

expresio(L,E1*E2):-
    append(L1,L2,L),
    L1\=[],L2\=[],
    expresio(L1,E1),
    expresio(L2,E2).

expresio(L,E1/E2):-
    append(L1,L2,L),
    L1\=[],L2\=[],
    expresio(L1,E1),
    expresio(L2,E2),
    Num is E2, % no volem divisio entre 0!
    Num =\= 0.
