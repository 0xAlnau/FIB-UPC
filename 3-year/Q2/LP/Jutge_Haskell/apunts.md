## Coses a tenir en compte per LP el parcial!!!
· Rationals de `import Data.Ratio`
    - es sol expressar com: `num % den`
    - té les funcions `denominator` i `numerator` per obtenir els valors respectius per a un racional r.
    - fer cas dels tipus que hi surtin, pendent de si cal utilitzar `toRational` per transformar en racional un enter.

· Tipus de ordre en un arbre binari:
    - `preOrder`: arrel + esq + dret
    - `postOrder`: esq + dret + arrel
    - `inOrder`: esq + arrel + dret

· Usar sort i group en llistes:
    - si es vol utilitzar aquestes funcions cal fer un `import Data.List (sort, group)`
    - `sort` serveix per a ordenar com sempre
    - `group` et crea subllistes dins de la llista que tenen un mateix valor
