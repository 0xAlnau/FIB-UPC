#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# COGNOM1:
# COGNOM2:
# NOM:
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

.data
res1:  .half  0
res2:  .half  0

vs:    .half  8, -6, 4, -2, 2, -4, 6, -8, 10, -10

.text
.globl main

#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# Escriu el codi de la teva subrutina a partir d'aquí
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

subr:
	addiu $sp, $sp, -24
	sw $s1, 12($sp)
	sw $s0, 16($sp)
	sw $ra, 20($sp)
	
	li $t7, 127 
	bltu $a1, $t7, else
	li $t1, 1
	li $t4, 2
	b fi_if
else:
	li $t1, 3
	li $t4, 4
	b fi_if
fi_if:
	lw $t2, 0($a2) #el que apunta p2
	addu $t3, $a1, $a2
	lw $t3, 0($t3) #el que apunta p2+p0
	sw $t2, 0($sp)
	sw $t3, 4($sp)
	sw $t1, 8($sp)
	
	move $s0, $a2
	move $s1, $t4
	move $a0, $sp
	jal suma
	
	sw $v0, 6($s0)
	
	lw $t1, 0($s0)
	addu $v0, $v0, $s1
	addu $v0, $v0, $t1
	
	lw $s1, 12($sp)
	lw $s0, 16($sp)
	lw $ra, 20($sp)
	addiu $sp, $sp, 24
	jr $ra
	
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# El codi que hi ha aqui es el de main i de la subrutina suma
# NO L'HAS DE TOCAR
# Es el que fa les dues crides a la teva funció
#*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
main:
    addiu $sp, $sp, -4
    sw    $ra, 0($sp)
        
    li    $a0, 1
    li    $a1, 0
    la    $a2, vs
    jal   subr
    la    $t0, res1
    sh    $v0, 0($t0)

    li    $a0, 2
    li    $a1, 255
    la    $a2, vs+4
    jal   subr
    la    $t0, res2
    sh    $v0, 0($t0)
    
    lw    $ra, 0($sp)
    addiu $sp, $sp, 4
    jr    $ra
    
suma:
    lh    $t0, 0($a0)
    lh    $t1, 2($a0)
    lh    $t2, 4($a0)
    addu  $v0, $t0, $t1
    addu  $v0, $v0, $t2    
    li    $t0, 0x88888888
    move  $t1, $t0
    move  $t2, $t0
    move  $t3, $t0
    move  $t4, $t0
    move  $t5, $t0
    move  $t6, $t0
    move  $t7, $t0
    move  $t8, $t0
    move  $t9, $t0
    move  $a0, $t0
    move  $a1, $t0
    move  $a2, $t0
    move  $a3, $t0
    jr    $ra
