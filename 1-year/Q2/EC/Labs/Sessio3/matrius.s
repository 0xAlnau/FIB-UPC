#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# COGNOM1:
# COGNOM2:
# NOM:
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

.data

MAT: .word   9, -1, -3, -2,
             1, -6,  9, 12,
            15,  2,  8,  2,
            19,  6, -2,  3

.text
.globl main

main:
      li $t0, -1
      li $t1, 3
      li $t8, 4
      la $t2, MAT
for1:
      addiu $t0, $t0, 1
      bge $t0, $t8, fi
for2:
      addiu $t9, $t0, -1
      ble $t1, $t9, for1
      sll $t3, $t0, 2
      addu $t3, $t3, $t1
      sll  $t3, $t3, 2 #T= 4 
      addu $t3, $t2, $t3 #calculem adreça
      lw $t4, 0($t3) #MAT[i][j]
      
      sll $t7, $t1, 2
      addu $t7, $t7, $t0
      sll  $t7, $t7, 2 #T= 4 
      addu $t7, $t2, $t7 #calculem adreça
      lw $t5, 0($t7) #MAT[j][i]
      
      li $t6, 3
      div $t4, $t6
      mfhi $t6 # %3
      li $s0, 0
      beq $t6, $s0, else
      and $s0, $t4, $t5
      b endfor
else: 
      li $s0, 17
      mult $t4, $s0
      mflo $s0
      b endfor
      
endfor:
      sw $s0, 0($t7)
      b for2
fi:
      jr  $ra 

