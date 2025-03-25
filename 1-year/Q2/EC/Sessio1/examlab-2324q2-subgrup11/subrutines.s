#---------------------------------------------
# COGNOM1: Cullell
# COGNOM2: Martinez
# NOM: Arnau
#-----------------------------------------------


.data
MOVs: .word 0
frase: .asciiz "move 0 --> 0 \n"

.text
.globl main

      
hanoi:
      addiu $sp, $sp, -24
      sw $s4, 0($sp)
      sw $s3, 4($sp)
      sw $s2, 8($sp)
      sw $s1, 12($sp)
      sw $s0, 16($sp)
      sw $ra, 20($sp)

      li $t1, 1
      bne $a3, $t1, else
      #ja estan als registres $a0 i $a1 els valors adequats
      jal mover
      li $v0, 1 # sum = 1
      b fi_if
      
else:
      move $s4, $a0
      move $s3, $a1
      move $s2, $a2
      move $s1, $a3
      
      #sa0 ja està preparat
      move $a1, $s2 #temp
      move $a2, $s3 #B
      addiu $a3, $s1, -1 #N-1
      jal hanoi
      
      move $s0, $v0 #c1 a segur
      move $a0, $s4 #A
      move $a1, $s3 #B
      jal mover
      
      move $a0, $s2 #temp
      move $a1, $s3 #B
      move $a2, $s4 #A
      addiu $a3, $s1, -1 #N-1
      jal hanoi
      
      addu $v0, $v0, $s0 #c2 + c1
      addiu $v0, $v0, 1 # +1
      
fi_if:
      lw $s4, 0($sp)
      lw $s3, 4($sp)
      lw $s2, 8($sp)
      lw $s1, 12($sp)
      lw $s0, 16($sp)
      lw $ra, 20($sp)
      addiu $sp, $sp, 24          
      jr $ra
            


#--------------------------------------------------------------------
# El codi que hi ha aqui es el del 'main' i de la subrutina 'mover'
# NO L'HAS DE TOCAR
#--------------------------------------------------------------------


main: 
      addiu $sp, $sp, -4
      sw $ra, 0($sp)
      
      li $a0, 'A'
      li $a1, 'B'
      li $a2, 'X'
      li $a3, 4
      jal hanoi
      
      la $t0, MOVs
      sw $v0, 0($t0)
      
      lw $ra, 0($sp)
      addiu $sp, $sp, 4
      jr $ra
      

mover:
      la $t0, frase
      sb $a0, 5($t0)
      sb $a1, 11($t0)
      
      move $a0, $t0
      li $v0, 4
      syscall

      move $t0, $zero
      move $t1, $zero
      move $t2, $zero
      move $t3, $zero
      move $t4, $zero
      move $t5, $zero
      move $t6, $zero
      move $t7, $zero
      move $t8, $zero
      move $t9, $zero
      move $a0, $zero
      move $a1, $zero
      move $a2, $zero
      move $a3, $zero
      move $v0, $zero
      
      jr $ra      
      

