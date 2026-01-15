%                   misioner, canibal canoa a costa 0
main:- EstadoInicial = [[3, 3],[0, 0],cc0], EstadoFinal = [[0, 0],[3, 3],cc1],
    between(1,1000,CosteMax),            % Buscamos solución de coste 0; si no, de 1, etc.
    camino( CosteMax, EstadoInicial, EstadoFinal, [EstadoInicial], Camino ),
    reverse(Camino, Camino1), write(Camino1), write(" con coste "), write(CosteMax), nl, halt.

camino(0,E,E,C,C).              % Caso base: cuando el estado actual es el estado final.
camino(CosteMax,EstadoActual,EstadoFinal,CaminoHastaAhora,CaminoTotal):-
    CosteMax>0,
    unPaso( CostePaso, EstadoActual, EstadoSiguiente ),  % En B.1 y B.2, CostePaso es 1.
    \+member( EstadoSiguiente, CaminoHastaAhora ),
    CosteMax1 is CosteMax-CostePaso,
    camino(CosteMax1, EstadoSiguiente, EstadoFinal, [EstadoSiguiente|CaminoHastaAhora], CaminoTotal).

unPaso(1, [[MisionersIniC0, CanibalsIniC0], [MisionersIniC1, CanibalsIniC1], cc0], [[MisionersFinC0, CanibalsFinC0], [MisionersFinC1, CanibalsFinC1], cc1]) :-
    between(0, 2, NMisioners), between(0, 2, NCanibals),
    NMisioners + NCanibals >= 1,
    NMisioners + NCanibals =< 2,
    NMisioners =< MisionersIniC0,
    NCanibals =< CanibalsIniC0,
    MisionersFinC1 is MisionersIniC1 + NMisioners,
    CanibalsFinC1 is CanibalsIniC1 + NCanibals,
    MisionersFinC0 is MisionersIniC0 - NMisioners,
    CanibalsFinC0 is CanibalsIniC0 - NCanibals,
    (MisionersFinC0 = 0 ; MisionersFinC0 >= CanibalsFinC0),
    (MisionersFinC1 = 0 ; MisionersFinC1 >= CanibalsFinC1).

unPaso(1, [[MisionersIniC0, CanibalsIniC0], [MisionersIniC1, CanibalsIniC1], cc1], [[MisionersFinC0, CanibalsFinC0], [MisionersFinC1, CanibalsFinC1], cc0]) :-
    between(0, 2, NMisioners), between(0, 2, NCanibals),
    NMisioners + NCanibals >= 1,
    NMisioners + NCanibals =< 2,
    NMisioners =< MisionersIniC1,
    NCanibals =< CanibalsIniC1,
    MisionersFinC1 is MisionersIniC1 - NMisioners,
    CanibalsFinC1 is CanibalsIniC1 - NCanibals,
    MisionersFinC0 is MisionersIniC0 + NMisioners,
    CanibalsFinC0 is CanibalsIniC0 + NCanibals,
    (MisionersFinC0 = 0 ; MisionersFinC0 >= CanibalsFinC0),
    (MisionersFinC1 = 0 ; MisionersFinC1 >= CanibalsFinC1).
