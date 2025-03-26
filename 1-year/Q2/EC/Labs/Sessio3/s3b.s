	# Sessio 3
	.data 
	.align 2
mat1: .space 120
mat4: .word 2, 3, 1, 2, 4, 3
col:  .word 2

	.text 
	.globl main
main:
	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	la $t1, mat4
	la $t2, col
	lw $t3, 8($t1)
	lw $t2, 0($t2)
	move $a0, $t1
	move $a1, $t3
	move $a2, $t2
	jal subr
	
	la $t1, mat1
	sw $v0, 108($t1)
	la $t1, mat4
	move $a0, $t1
	li $a1, 1
	li $a2, 1
	jal subr
	
	la $t1, mat1
	sw $v0, 0($t1)
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra

subr:
	li $t0, 3 #NC
	mult $t0, $a1
	mflo $t0
	addu $t0, $t0, $a2
	sll $t0, $t0, 2
	addu $t0, $t0, $a0
	lw $t0, 0($t0)
	
	li $t1, 24
	mult $t1, $a2
	mflo $t1
	la $t2, mat1
	addiu $t2, $t2, 20
	addu $t1, $t1, $t2
	sw $t0, 0($t1)
	move $v0, $a1
	jr $ra


