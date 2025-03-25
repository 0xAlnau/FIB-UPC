# FITXER PLANTILLA PER A LA PREGUNTA 3.
# NO S'HA DE MODIFICAR NI S'HA DE LLIURAR

    .data
V:  .word   0, 0, 0, 0
M:  .word   0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
    .word   0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
    .word   0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3

    .text
    .globl main
main:
    move $t0, $zero
    li   $t3, 12
    la   $t6, M
fori:
    bge  $t0, $t3, fifori
    la   $t5, V           # inicialitzem $t5, punter a V[0]
    la   $t6, M
    sll  $t7, $t0, 4
    addu $t6, $t6, $t7    # inicialitzem $t6, punter a M[i][0]
    move $t1, $zero
    li   $t4, 4
forj:
    bge  $t1, $t4, fiforj

    # Llegim M[i][j] a memòria
    lw   $t2, 0($t6)      # aux = M[i][j]

    # Llegim V[j] a memòria
    lw   $t7, 0($t5)      # $t7 = V[j]

    # Sumem i escrivim V[j] a memòria
    addu $t7, $t7, $t2
    sw   $t7, 0($t5)      # V[j] = $t7 + aux

    # incrementem els punters i el comptador j
    addiu $t6, $t6, 4
    addiu $t5, $t5, 4
    addiu $t1, $t1, 1     # j++
    b     forj
fiforj:
    addiu $t0, $t0, 1     # i++
    b     fori
fifori:
    jr    $ra

