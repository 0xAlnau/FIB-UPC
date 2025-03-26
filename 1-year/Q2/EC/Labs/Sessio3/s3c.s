	# Sessio 3

	.data 
mat:	.word 0,0,2,0,0,0
	.word 0,0,4,0,0,0
	.word 0,0,6,0,0,0
	.word 0,0,8,0,0,0
	
resultat: .word 0

	.text 
	.globl main
main:
	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	la $a0, mat
	jal suma_col
	
	la $t0, resultat
	sw $v0, 0($t0)
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra
	
suma_col:
	li $t0, 0
	move $t1, $a0
	addiu $t1, $t1, 8
	addiu $t2, $a0, 84
for:
	lw $t3, 0($t1)
	addu $t0, $t0, $t3
	addiu $t1, $t1, 24
	blt $t1, $t2, for
	
	move $v0, $t0
	jr $ra




