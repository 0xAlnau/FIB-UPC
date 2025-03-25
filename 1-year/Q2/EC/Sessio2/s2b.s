	.data
result: .word 0
num:	.byte ';'

	.text
	.globl main
main:
	la $t0, num
	lb $t0, 0($t0)
	li $t1, 'a'
	blt $t0, $t1, con2
	li $t1, 'z'
	ble $t0, $t1, final
con2:   
	li $t1, 'A'
	blt $t0, $t1, if
	li $t1, 'Z'
	bgt $t0, $t1, if
	b final
if:
	li $t1, '0'
	blt $t0, $t1, else
	li $t1, '9'
	bgt $t0, $t1, else
	addiu $t0, $t0, -48
	b final
else:
	li $t0, -1
final:
	la $t1, result
	sw $t0, 0($t1)
	

# COPIA EL TEU CODI AQUI

	jr $ra

