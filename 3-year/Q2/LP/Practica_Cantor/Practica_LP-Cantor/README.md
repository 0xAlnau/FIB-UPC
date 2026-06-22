# LP Q2-2025/26: funcions de Cantor
En aquest repositori es troba la pràctica realitzada en Llenguatge de Programació, en la qual s'ha implementat un intèrpret d'un llenguatge de programació minimalista. Aquest nou llenguatge es basa en funcions amb un sol paràmetre i funcions **d'aparellament de Cantor**. Per a realitzar la pràctica s'ha utilitzat Python i Antlr4, exactament la versió **4.13.1**

## Background
### Funcions d'aparellament
Una funció d'aparellament és aquella que és capaç d'agafar dos nombres naturals i fer una transformació per arribar-hi a un altre nombre natural. Es a dir, dos nombres naturals permeten codificar un i només un natural. Són de la forma:  
`π : N × N → N`

### Funció de Cantor
És una funció d'aparellament, i és del tipus:  
`π(x,y) = (x² + x + 2xy + 3y + y²) / 2`    
Durant la resta del document ens referirem a π(x,y) com a <x.y>.

La seva **inversa**, amb valors intermedis, és la següent:  
`z = valor inicial`  
`w = floor((sqrt(8z + 1) - 1) / 2)`  
`t = (w² + w) / 2`  
`y = z - t`  
`x = w - y`  

## Possibilitats del llenguatge de programació Cantorià
És un llenguatge minimalista funcional, i per tant, no hi ha variables que es puguin utilitzar. L'estructura d'un codi cantorià (.cantor) és la següent:

```
# podem posar comentaris
main X      # declarem que el programa entrarà per la funció X
extended    # és opcional

import Y    # podem importar codi d'un fitxer Y (sense el .cantor)

define Z
    [això és un altre comentari sobre funció Z]
    tipus1 f1 f2

define X
    [un altre comentari]
    tipus2 f1 f2 Z
```

### Comportament de les funcions
Les paraules `tipus1` i `tipus2` es refereixen a possibles funcions predeterminades del llenguatge. Les funcions `tipus1` són aquelles que es poden utilitzar sense el mode **extended**, i són les següents:

- `comp f g`: donades dues funcions `f` i `g` comp és la composició de les dues funcions, es a dir, es calcula `f(g(x))`. On x és l'entrada de l'usuari.
- `pair f g`: donades dues funcions `f` i `g` pair calcula la funció de Cantor: `<f(x).g(x)>`.
- `mu f`: serveix per a implementar la recursivitat bàsica gràcies a la minimització `μ`. El que es fa és anar iterant des de 0 fins al infinit, llavors l'interpret fa l'aparellament <x.i> i se'l passa a la funció `f`. Aquesta funció `f` ha de retornar 0 o 1, si retorna 1 llavors retorna el valor `i` i acaba, sinó segueix buscant fins a complir la condició de la funció `f`.

Les funcions `tipus2` requereixen de posar `extended` al programa, i són les següents:

- `compair f g h`: donades les funcions `f`, `g` i `h` compair calcula `f(<g(x).h(x)>)`.
- `primrec f g h`: donades les funcions `f`, `g` i `h` primrec serveix per a problemes recursius on els passos per a resoldre el problema segueixen la sèrie: `0, 1, 2, ..., x`, com per exemple Fibonacci. La funció `f` ens retorna un 1 o un 0, indicant si estem a un cas base. La funció `g` retorna el valor associat a estar en un cas base. La funció `h` retorna el valor associat al cas recursiu. primrec retorna una tupla dels valors: `s(x), s(x-1), s(x-2), ..., s(1), s(0)` per a poder anar tractant els casos recursius.

### Funcions amb comportament predefinit
Hi ha funcions que ja tenen un comportament predefinit i que no cal definir al programa, aquestes funcions són:

- `k_1`: retorna la constant 1
- `id`: donat un `<x.y>` retorna el mateix `<x.y>`
- `add`: donat un `<x.y>` retorna `x + y`
- `mul`: donat un `<x.y>` retorna `x * y`
- `diff`: donat un `<x.y>` retorna `max(0, x - y)`, ja que només tractem naturals.
- `fst`: donat un `<x.y>` retorna `x`
- `snd`: donat un `<x.y>` retorna `y`

Aquestes funcions (juntament amb les que hem definit al programa) són les que poden pendre el lloc de `f1` i `f2`. Ara amb un exemple es podrà compendre millor com funciona tot:

```
# relacionals.cantor
main eq
extended
import booleans


define swapDiff
    [donats <x.y> retorna la diferencia y - x]
    compair diff snd fst

define lt
    [donat <x.y> retorna 1 si x < y]
    comp signe swapDiff


define gt
    [donat <x.y> retorna 1 si x > y]
    comp signe diff


define neq
    [donat <x.y> retorna 1 si x != y]
    compair signe lt gt


define eq
    [donat <x.y> retorna 1 si x == y]
    comp not neq
```

## Com utilitzar l'intèrpret del llenguatge
El repositori consta de 4 carpetes:

- `Inputs`: aquí podem trobar els fitxers .inp per a poder fer les proves i execucions.
- `InterpretCantor`: dintre hi podem trobar la gramàtica en el fitxer `cantor.g4`, el comportament de l'intèrpret al fitxer `cantor.py`, el `Makefile` i finalment un script `run.sh` per a executar tots els tests de prova d'un cop.
- `Outputs`: per cada tasca de la pràctica hi ha una carpeta amb els jocs de prova corresponents a cada exercici.
- `ScriptsCantor`: dintre hi ha tots els fitxers `.cantor`.

Una vegada t'has descarregat el repositori cal seguir les següents passes:

1. Entrar a `InterpretCantor`, obrir una terminal i fer `make`. Si tot ha anat correctament s'hauran generat els fitxers d'ANTLR.
2. Si es volen executar els jocs de prova cal posar a la terminal: `./run.sh`. Si et diu que no tens permissos abans cal posar: `chmod +x run.sh`.
3. Ara a la carpeta `Outputs` s'hauran creat els fitxers .out o s'hauran sobreescrit si ja hi eren.

Per a instal·lar antlr en la versió 4.13.1 es pot fer amb la comanda: `antlr4 -v 4.13.1`

### Com executar un script .cantor
Per a executar només un script de Cantor i que el resultat surti per la terminal cal fer una comanda com la següent: `echo "numeros" | python3 cantor.py fitxer.cantor`

- `numeros` és una llista de nombres, per exemple: `"1 2 3"`.
- `fitxer.cantor` és l'script que es vol executar de la carpeta `ScriptsCantor`.

Un exemple executat en la carpeta `InterpretCantor` és el següent:  
`echo "1 2 3" | python3 cantor.py add3.cantor`  
Retornaria `6`.  

Si es vol utilitzar fitxers com a entrades i/o sortides es podria fer fent:  
`python3 cantor.py add3.cantor <123.inp> 123.out`  
El fitxer `123.inp` ha d'estar en la mateixa carpeta, i la comanda generarà el fitxer `123.out`.

## Decisions de disseny
Durant la pràctica he hagut d'anar prenent diferents decisions de disseny, aquestes han sigut les més importants:

- `Implementació de les funcions com add`: aquestes funcions predefinides del llenguatge les he implementat amb un diccionari `func_basic`, tal i com vam fer als exercicis de laboratori. El diccionari té com a key el nom de la funció i retorna la `funció lambda` corresponent.

- `Imports`: l'apartat dels imports al principi els vaig implementar amb una funció recursiva, on anava llegint el fitxer sencer buscant la paraula `import`. Em vaig adonar a mig camí que no era la forma adecuada, i al final vaig decidir de provar a generar un nou arbre amb el fitxer importat i guardar les funcions noves, la qual cosa va funcionar i és tal com està implementat actualemnt.

- `Gramàtica`: la gramàtica ha sigut dissenyada inspirant-me en la gramàtica dels exercicis de laboratori, ja que aquesta última era molt completa i similar a la demanada en la pràctica.

