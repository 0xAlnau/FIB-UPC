.globl main
main:
	li $t0, -3
	sra $t1, $t0, 31
	xor $t0, $t0, $t1
	subu $t0, $t0, $t1
	sll $t1, $t1, 31
	or $t0, $t0, $t1