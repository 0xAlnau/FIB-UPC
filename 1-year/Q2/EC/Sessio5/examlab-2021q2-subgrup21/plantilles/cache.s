##############################################################################
#                      AQUEST FITXER NO S'HA DE LLIURAR                      #
##############################################################################

	.data

vect:	.word 0, 1, 2, 3, 4, 5, 6, 7

matx:	.word  1,  2,  3,  4,  5,  6,  7,  0
	.word  1,  2,  3,  4,  5,  6,  0,  8
	.word  1,  2,  3,  4,  5,  0,  7,  8
	.word  1,  2,  3,  4,  5,  0,  7,  8
	.word  1,  2,  3,  4,  5,  6,  7,  8
	.word  1,  2,  3,  4,  0,  6,  7,  8
	.word  1,  2,  3,  4,  5,  6,  7,  8
	.word  0,  2,  3,  4,  5,  6,  7,  8

	.text
	.globl main
main:
	la	$t0, vect		# punter a vect
	la	$t1, matx 		# punter a matx
	move	$t2, $zero		# i=0
	li	$t3, 8
for_i:
	bge	$t2, $t3, fi_for_i
	move	$t4, $zero		# j=0
	move	$t5, $t0		# punter a vect
for_j:
	bge	$t4, $t3, fi_for_j
	lw	$t6, 0($t1)
	addiu	$t1, $t1, 4		# avancem punter a matr

	lw	$t7, 0($t5)
	subu	$t7, $t7, $t6
	sw	$t7, 0($t5)
	addiu	$t5, $t5, 4		# avancem punter a vect
	addiu	$t4, $t4, 1		# j++
	b	for_j
fi_for_j:
	addiu	$t2, $t2, 1		# i++
	b	for_i
fi_for_i:
	jr	$ra

