main:- EstadoInicial = [[1,2,5,8],[],ll0], EstadoFinal = [[],[1,2,5,8],ll1],
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


% movem 2 persones de esq a dre
unPaso(Cost, [Esq, Dre, ll0], [EsqNew, DreNew, ll1]) :-
    select(P1, Esq, Rest1),     % persona1
    select(P2, Rest1, EsqNew),  % persona2 i creem nou grup
    P1 < P2,                    % evitar duplicats
    Cost is max(P1, P2),        % volem el mes lent
    ord_union([P1, P2], Dre, DreNew). % es com fer append mes sort

% movem 1 persona de esq a dre
unPaso(Cost, [Esq, Dre, ll0], [EsqNew, DreNew, ll1]) :-
    select(P1, Esq, EsqNew),
    Cost is P1,
    ord_add_element(Dre, P1, DreNew). % afegim


% movem 1 persona de dre a esq
unPaso(Cost, [Esq, Dre, ll1], [EsqNew, DreNew, ll0]) :-
    select(P1, Dre, DreNew),
    Cost is P1,
    ord_add_element(Esq, P1, EsqNew).

% movem 2 persones de dre a esq
unPaso(Cost, [Esq, Dre, ll1], [EsqNew, DreNew, ll0]) :-
    select(P1, Dre, Rest1),
    select(P2, Rest1, DreNew),
    P1 < P2,
    Cost is max(P1, P2),
    ord_union([P1, P2], Esq, EsqNew).
