	.data

	.text
	.globl main
main:
	li $s1, 23 # Y
	li $s0, 8  # X

	li $t0, 1
	sllv $s0, $s0, $t0
	addiu $s0, $s0, -1
	xor $s1, $s1, $s0

	jr $ra
