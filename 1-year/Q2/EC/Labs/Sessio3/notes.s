#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# COGNOM1:
# COGNOM2:
# NOM:
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

.data

# Cada columa de notes guarda totes les notes d'un examen. Com hi ha quatre columnes, vol dir que hi ha quatre examens
# Cada columa té 5 element perquè només hi ha cinc alumnes

NOTES: .half 	1, 2  3, 4, 
            	1, 2  3, 5,
            	1, 2  3, 6, 
            	1, 2  3, 7,
            	1, 2  3, 8

NumExam: .byte 2

HISTO: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.text
.globl main

main:
      la $t0, NumExam
      lb $t0, 0($t0) #num exam
      sll $t0, $t0, 1 #mult por 2
      la $t1, NOTES
      addu $t1, $t1, $t0 #saber donde empiezo columna
      
      li $t3, 8 #stride
      addiu $t4, $t1, 40 #limit donde acabo for
      la $t9, HISTO
for:
      lh $t5, 0($t1) #extrec nota
      sll $t6, $t5, 2 #accede a HISTO[i]
      addu $t6, $t6, $t9
      lw $t7, 0($t6)
      addiu $t7, $t7, 1
      sw $t7, 0($t6)
      addu $t1, $t1, $t3 #sumo stride
      blt $t1, $t4, for
      
      jr $ra

