main:- EstadoInicial = [0,0], EstadoFinal = [8,8], N = 8, P = 100,
    between(1,1000,CosteMax),            % Buscamos solución de coste 0; si no, de 1, etc.
    camino( CosteMax, EstadoInicial, EstadoFinal, [EstadoInicial], Camino, N, P ),
    reverse(Camino, Camino1), write(Camino1), write(" con coste "), write(CosteMax), nl, halt.

camino(0,E,E,C,C,_,_).              % Caso base: cuando el estado actual es el estado final.
camino(CosteMax,EstadoActual,EstadoFinal,CaminoHastaAhora,CaminoTotal,N,P):-
    CosteMax > 0,
    CosteMax < P,
    unPaso( CostePaso, N, EstadoActual, EstadoSiguiente ),  % En B.1 y B.2, CostePaso es 1.
    \+member( EstadoSiguiente, CaminoHastaAhora ),
    CosteMax1 is CosteMax-CostePaso,
    camino(CosteMax1, EstadoSiguiente, EstadoFinal, [EstadoSiguiente|CaminoHastaAhora], CaminoTotal, N, P).

unPaso(1, N, [FilAct, ColAct], [FilSeg, ColSeg]) :-
    member([SaltX,SaltY], [[1,2],[-1,2],[-2,1],[-2,-1],[2,1],[2,-1],[-1,-2],[1,-2]]),
    FilSeg is FilAct + SaltX,
    ColSeg is ColAct + SaltY,

    FilSeg >= 0, FilSeg =< N,
    ColSeg >= 0, ColSeg =< N.
