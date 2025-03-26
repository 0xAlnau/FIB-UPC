
# FITXER DE PROVES PER A LA PREGUNTA 3.
# NO S'HA DE MODIFICAR NI S'HA DE LLIURAR

    .data
A:      .word 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,

        .align 2
MAXpar: .space 48

    .text
    .globl main

main:

    li      $t0, 24               
    li      $t1, 0                # i = 0
    la      $t2, A                # t2 <- @A[0]
    la      $t3, MAXpar           # t3 <- @MAXpar[0] 

for:

    lw      $t4, 0($t2)           # t4 <- A[i]
    lw      $t5, 4($t2)           # t5 <- A[i+1]

    ble     $t4, $t5, else        # si (t4 <= t5) go else
    sw      $t4, 0($t3)           # MAXpar[i] <-- A[i]
    b       fi
else:
    sw      $t5, 0($t3)           # MAXpar[i] <-- A[i+1]
fi:

    addiu   $t2, $t2, 8           # t2 <- @A[i+2] 
    addiu   $t3, $t3, 4           # t3 <- @MAXpar[i+1]
    addiu   $t1, $t1, 2           # i = i + 2
    blt     $t1, $t0, for         # si (i < 24) goto for 

    jr      $ra


