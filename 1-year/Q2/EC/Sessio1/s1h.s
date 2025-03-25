# PRACTICA 1 #######################

		.data
cadena: .byte -1, -1, -1, -1, -1, -1
vec:    .word 5, 6, 8, 9, 1

		.text
	.globl main
main:
	li $s0, 0 #i = 0
	li $t0, 5 #protocol aturada
while: 
	bge $s0, $t0, fi
	la $t1, cadena 
	addu $t2, $t1, $s0 #cadena[i]
	la $t3, vec
	li $t4, 4
	subu $t4, $t4, $s0 # 4- i
	sll $t4, $t4, 2 # nova i * 4
	addu $t3, $t3, $t4
	lw  $t3, 0($t3)
	addiu $t3, $t3, 0x30
	addu $t1, $t1, $s0
	sb $t3, 0($t1) # guarda la suma en cadena[i]
	addiu $s0, $s0, 1 #++i
	b while
	
fi:
	li $t4, 0
	sb $t4, 5($t1) #cadena[5] = 0
	
	li $v0, 4
	la $a0, cadena
	syscall

	jr $ra		# main retorna al codi de startup

