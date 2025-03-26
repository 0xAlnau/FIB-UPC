# PRACTICA 1 #######################

		.data
	A: .word 3, 5, 7
	punter: .word 0

		.text
	.globl main
main:
	la $t1, A
	addiu $t1, $t1, 8 #calculem adreça A[2]
	la $t2, punter
	sw $t1, 0($t2)

	lw $t2, 0($t2)
	lw $t2, 0($t2)
	addiu $s0, $t2, 2 #temp = lo que apunta punter +2
	
	la $t1, punter
	lw $t1, 0($t1)
	lw $t1, -8($t1) #el contenido que apunta punter pero -2 words
	addu $s0, $t1, $s0 
	
	la $t1, A
	sw $s0, 4($t1)

	li $v0, 1
	move $a0, $s0
	syscall
	
	jr $ra		# main retorna al codi de startup

