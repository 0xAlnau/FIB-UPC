#---------------------------------------------
# COGNOM1: Cullell
# COGNOM2: Martinez
# NOM: Arnau
#-----------------------------------------------

.data
dIN: .half 1, 2, 3, 4, 5, 6, 
           2, 3, 4, 5, 6, 7, 
           3, 4, 5, 6, 7, 8, 
           4, 5, 6, 7, 8, 9, 
           5, 6, 7, 8, 9, 10, 
           6, 7, 8, 9, 10, 11
      .align 2

dOUT: .space 64


.text
.globl main

main:
      li $t4, 4
      li $t3, 6 # NC = 6
      li $t0, 1 # i = 1
for1:
      bgt $t0, $t4, fi_for1
      li $t1, 1 # j = 1
for2:
      bgt $t1, $t4, fi_for2
      la $t9, dIN
      
      addiu $t5, $t0, 1 # i+1
      mult $t3, $t5
      mflo $t5 #NC * i
      addu $t5, $t5, $t1 #+j
      sll $t5, $t5, 1 #multipliquem per 2
      addu $t5, $t5, $t9 #&dIN[i+1][j]
      
      mult $t3, $t0 
      mflo $t6 #NC * i
      addu $t6, $t6, $t1 #+j
      addiu $t6, $t6, -1 #-1
      sll $t6, $t6, 1 #multipliquem per 2
      addu $t6, $t6, $t9 #&dIN[i][j-1]
      
      mult $t3, $t0 
      mflo $t7 #NC * i
      addu $t7, $t7, $t1 #+j
      addiu $t7, $t7, 1 #+1
      sll $t7, $t7, 1 #multipliquem per 2
      addu $t7, $t7, $t9 #&dIN[i][j+1]
      
      lhu $t5, 0($t5)
      lhu $t6, 0($t6)
      lhu $t7, 0($t7)
      
      addu $t5, $t5, $t6
      addu $t5, $t5, $t7
      
      addiu $t6, $t0, -1 # i-1
      addiu $t7, $t1, -1 # j-1
      mult $t4, $t6 # 4*i
      mflo $t6
      addu $t6, $t6, $t7
      sll $t6, $t6, 2 #multipliquem per 4
      la $t7, dOUT
      addu $t6, $t6, $t7 #&dOUT[i-1][j-1]
      sw $t5, 0($t6)
      
      addiu $t1, $t1, 1 #j++
      b for2
fi_for2:
      addiu $t0, $t0, 1 #i++
      b for1
fi_for1:
      jr $ra
	
