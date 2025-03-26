# PRACTICA 1 #######################

		.data
	.align 2
fib:    .space 40
 
		.text
	.globl main
main:
	li $s0, 2
	la $t1, fib
	li $t2, 0
	sw $t2, 0($t1)
	li $t2, 1 #guardo en fib[0] 0
	sw $t2, 4($t1) #guardo en fib[1] 1

while:
	slti $t0, $s0, 10 #evalua si i == 10
	beq $t0, $zero, fi 
	
	sll $t2, $s0, 2 #i*4
	addu $t2, $t2, $t1 #fib[i]
	lw $t3, -4($t2) #fib[i-1]
	lw $t4, -8($t2) #fib[i-2]
	addu $t5, $t3, $t4
	sw $t5, 0($t2)
	
	addiu $s0, $s0, 1
	b while
fi:
	jr $ra		# main retorna al codi de startup

