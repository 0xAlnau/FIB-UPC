// Gramàtica per expressions senzilles
grammar exprs;
root : expr EOF
     ;
expr : '(' mig=expr ')'                                  # parent
     | esq=expr op=(MUL | POW | DIV | MOD) dre=expr      # binari
     | esq=expr op=(ADD | SUB) dre=expr                  # binari
     | NUM                                               # numero
     ;
NUM : [0-9]+ ;
POW : '^' ;
MUL : '*' ;
DIV : '/' ;
MOD : '%' ;
ADD : '+' ;
SUB : '-' ;
WS  : [ \t\n\r]+ -> skip ;
