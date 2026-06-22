// Gràmatica del llenguatge de programació Cantor
grammar cantor;
root : (NUM)* main (exte)? (impo)* (deFu)* EOF
     ;

main : MAIN func                                                 # mainI
     ;

exte : EXTENDED                                                  # extended
     ;

impo : IMPORT NOMF                                               # importa
     ;

deFu : DEFINE NOMF op=(PAIR | COMP) f=func g=func                # function
     | DEFINE NOMF op=(COMPAIR | PRIMREC) f=func g=func h=func   # function
     | DEFINE NOMF op=MU f=func                                  # function
     ;

func : NOMF                                                      # nomFunction
     | un=(K | ID)                                               # unaria
     | bi=(FST | SND)                                            # binaria
     | bi=MUL                                                    # binaria
     | bi=(ADD | DIF)                                            # binaria
     ;



MAIN : 'main' ;
K  : 'k_1' ;
ID : 'id' ;
FST : 'fst' ;
SND : 'snd' ;
ADD : 'add' ;
MUL : 'mul' ;
DIF : 'diff' ;
DEFINE : 'define' ;
PAIR : 'pair' ;
COMP : 'comp' ;
COMPAIR : 'compair' ;
PRIMREC : 'primrec' ;
MU : 'mu' ;
IMPORT : 'import' ;
EXTENDED : 'extended' ;

NUM : [0-9]+ ;
NOMF : [a-zA-Z0-9_]+ ;
COMMENT : ('#' | '[') ~[\r\n]* -> skip ; //eliminar tot després de # o [ excepte salt linia
WS  : [ \t\n\r]+ -> skip ;
