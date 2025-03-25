###############################################################################
# NOM: Arnau
# COGNOMS: Cullell Martínez
###############################################################################

		.data
LENGTH:		.byte 10
		.align 5
V:		.word 2, 3, 5, -1, 1, 8, 6, 7, 1, -2

		.text
		.globl main


main:
		addiu $sp, $sp, -16
		sw $ra, 0($sp)
	
		la	$s0, V
		li	$s1, 0
		la	$s2, LENGTH
		lw	$s2, 0($s2)
for_main:
		addiu	$t4, $s2, -1
		bge	$s1, $t4, fi_for_main
		move	$a0, $s0
		move	$a1, $s1
		move	$a2, $s2
		jal	subr
		addiu	$s1, $s1, 1
		b for_main
fi_for_main:
	
		lw	$ra, 0($sp)
		addiu	$sp, $sp, 16
		jr	$ra


subr:
# Escriviu aquí el codi de la subrutina
addiu $sp, $sp, -20
sw $ra, 0($sp)
sw $s0, 4($sp)
sw $s1, 8($sp)
sw $s2, 12($sp)
sw $s3, 16($sp)

move $s0, $a0
move $s1, $a1
move $s2, $a2
addiu $t8, $a1, 1
move $s3, $t8
for:
bge $s3, $s2, fi_for
sll $t1, $s1, 2 #multipliquem i per 4
sll $t2, $s3, 2 #multipliquem j per 4
addu $t1, $s0, $t1 #adreça de vec[i]
addu $t2, $s0, $t2 #adreça de vec[j]

lw $t4, 0($t1)
lw $t5, 0($t2)

ble $t5, $t4, fi
#sino
move $a0, $t2
move $a1, $t1
jal canvia

fi:
addiu $s3, $s3, 1 # ++j
b for

fi_for:
lw $ra, 0($sp)
lw $s0, 4($sp)
lw $s1, 8($sp)
lw $s2, 12($sp)
lw $s3, 16($sp)
addiu $sp, $sp, 20
jr $ra






# No modifiqueu el codi a partir d'aquí
canvia:
		addiu	$sp, $sp, -16
		sw	$ra, 0($sp)
		sw	$s0, 4($sp)
		sw	$s1, 8($sp)
		move	$s0, $a0
		move	$s1, $a1
	
		jal	embruta

		lw	$t0, 0($s0)
		lw	$t1, 0($s1)
		sw	$t0, 0($s1)
		sw	$t1, 0($s0)
	
		move	$a0, $s0
		move	$a1, $s1
		lw	$ra, 0($sp)
		lw	$s0, 4($sp)
		lw	$s1, 8($sp)
		addiu	$sp, $sp, 16
	
		jr	$ra

	
embruta:
		li	$t0, 0x12345678
		move	$t1, $t0
		move	$t2, $t0
		move	$t3, $t0
		move	$t4, $t0
		move 	$t5, $t0
		move	$t6, $t0
		move 	$t7, $t0
		move 	$t8, $t0
		move 	$t9, $t0
		move	$a0, $t0
		move	$a1, $t0
		move	$a2, $t0
		move	$a3, $t0
		jr	$ra
