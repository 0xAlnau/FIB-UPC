	.data

n10:	.word 0
n11:	.word 0

	.text
	.globl main

ackermann:
# Escriu aqui el teu codi de la funcio ackermann

main:
	addiu $sp, $sp, -4
  	sw    $ra, 0($sp) 

   	li    $a0, 1
   	li    $a1, 0
   	jal   ackermann
   	
   	la    $t0, n10
   	sw    $v0, 0($t0)
   	
	move  $a0, $v0
   	li    $v0, 1
   	syscall
   	
   	li    $a0, 1
   	li    $a1, 1
   	jal   ackermann
   	
   	la    $t0, n11
   	sw    $v0, 0($t0)

	move  $a0, $v0
   	li    $v0, 1
   	syscall

   	lw    $ra, 0($sp)
   	addiu $sp, $sp, 4
   	jr    $ra
