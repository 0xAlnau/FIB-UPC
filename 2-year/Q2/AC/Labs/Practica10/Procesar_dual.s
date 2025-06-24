.data
	.align 16
	zeros: .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	uns: .byte 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

.text
	.align 4
	.globl procesar
	.type procesar, @function
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo

	movl $0, %eax # i = 0

	movl 16(%ebp), %edi  # edi = n
	imul %edi, %edi # edi = n*n

	movl 8(%ebp), %esi # esi = @mata
	movl 12(%ebp), %edx # edx = @matb

	movdqa uns, %xmm2 # posem uns
	movdqa zeros, %xmm3 # posem zeross
for:
	cmpl %edi, %eax # i - n*n
	jge fi_for

	#comprovacio 1
	movl %esi, %ebx # ebx = @mata
	andl $0xf, %ebx # comprovem residu
	cmpl $0, %ebx # fem la resta
	je else # si son els dos 0 (iguals) es multiple de 16 i fem movdqa
if:
    movdqu (%esi, %eax), %xmm0 # guardem 16 posicions de la mata
    jmp fi_if
else:
    movdqa (%esi, %eax), %xmm0 # guardem 16 posicions de la mata
fi_if:

	pand %xmm2, %xmm0 # fem la pand amb les 16 posicions de mata
	pcmpgtb %xmm3, %xmm0 # xmm0 - 0 en cada posicio, posa 255 (true) si la posicio > 0, o 0 al reves

	#compravacio 2
	movl %esi, %ebx # ebx = @mata
	andl $0xf, %ebx # comprovem residu
	cmpl $0, %ebx # fem la resta
	je else2 # si son els dos 0 (iguals) es multiple de 16 i fem movdqa
if2:
    movdqu %xmm0, (%edx, %eax) # guardem 16 posicions de la mata
    jmp fi_if2
else2:
    movdqa %xmm0, (%edx, %eax) # guardem 16 posicions de la mata
fi_if2:

	addl $16, %eax # i += 16
	jmp for
fi_for:

# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
