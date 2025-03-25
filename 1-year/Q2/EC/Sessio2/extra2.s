.data
D:	.word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
.text
.globl main
main:
	li $t0, 0
	li $t1, 12
	li $t3, 10
	la $t4, D
while:
	bge $t0, $t3, final
	addu $t5, $t1, $t0
	sw $t5, 0($t4)
	addiu $t4, $t4, 4
	addiu $t0, $t0, 1
	b while
final:
	jr $ra