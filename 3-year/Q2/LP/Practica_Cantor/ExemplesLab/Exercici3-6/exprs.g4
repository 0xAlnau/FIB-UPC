// Gramàtica per expressions senzilles
grammar exprs;
root : (inst)* EOF
     ;

inst : ESCRIU expr                                       # escriptura
     | VAR ASSIGNA expr                                  # assignacio
     | IF expBo=exBo THEN (inst)* END                    # if
     | WHILE expBo=exBo DO (inst)* END                   # while
     ;

exBo : esq=expr op=(EQU | LT | GT | DIF) dre=expr            # binariBool
     | VALB                                              # casBase
     ;

expr : '(' mig=expr ')'                                  # parent
     | esq=expr op=POW dre=expr                          # binari
     | esq=expr op=(MUL | DIV | MOD) dre=expr            # binari
     | esq=expr op=(ADD | SUB) dre=expr                  # binari
     | NUM                                               # numero
     | VAR                                               # variab
     ;

IF : 'if' ;
THEN : 'then' ;
WHILE : 'while' ;
DO : 'do' ;
END : 'end' ;
VALB : ('TRUE' | 'FALSE') ;
ASSIGNA : ':=' ;
ESCRIU : 'write' ;
NUM : [0-9]+ ;
VAR : [a-z]+ ;
EQU : '=' ;
LT : '<' ;
GT : '>' ;
DIF : '<>' ;
POW : '^' ;
MUL : '*' ;
DIV : '/' ;
MOD : '%' ;
ADD : '+' ;
SUB : '-' ;
WS  : [ \t\n\r]+ -> skip ;
