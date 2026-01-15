:- use_module(library(clpfd)).

example( 0,  26, [1,2,5,10]           ).  % Solució: [1,0,1,2]
example( 1, 361, [1,2,5,13,17,35,157] ).

main :- 
    example(0, Amount, Coins),
    nl, write('Paying amount '), write(Amount), write(' using the minimal number of coins of values '), write(Coins), nl, nl,

%1: Variables i dominis:
    length(Coins, N), 
    length(Vars,  N),           % obté una llista de N variables prolog
    Vars ins 0..Amount,         % en el pitjor dels casos, només hi ha monedes de valor 1...

%2: Constraints:
    % Generem la restricció fent servir el predicat scalar_product/4 definit a library(clpfd):
    scalar_product(Coins, Vars, #=, Amount),
    % O de forma alternativa, com abans:
    % exprProdEscalar( Vars, Coins, ExprProdEsc ),  % per exemple expr( [X1,X2,X3,X4], [1,2,5,10],   X4*10 + X3*5 + X2*2 + X1*1 )
    % ExprProdEsc #= Amount,

%3: Labeling:
    exprSuma( Vars, ExprSum ),  % per exemple exprSuma( [X1,X2,X3,X4], X4+X3+X2+X1 )
    labeling( [min(ExprSum)], Vars ),

%4: Escrivim el resultat:
    NumCoins is ExprSum, write('We need '), write(NumCoins), write(' coins: '), write(ExprSum), nl, nl, halt.


% exprProdEscalar(+Vars, +Coins, ?Expr): atenció! aquest predicat no "calcula" res! Només genera un
%                                        terme prolog que és la expressió corresponent al producte escalar
%                                        de les llistes Vars i Coins
exprProdEscalar( [], [], 0 ).
exprProdEscalar( [X|Vars], [K|Coins], Expr + X*K ) :- exprProdEscalar( Vars, Coins, Expr ).

%exprSuma(+Vars, ?Expr): com en el predicat anterior, aquest predicat se satisfà si Expr és
%                        l'expressió formada per la suma dels dels elements de la llista Vars.
exprSuma( [X],      X ) :- !.
exprSuma( [X|Vars], X+Expr ) :- exprSuma( Vars, Expr).
