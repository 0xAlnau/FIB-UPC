.data
.align 16
zeros: .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
uns: .byte 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

.text
	.align 4
	.globl procesar
	.type	procesar, @function
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

	movdqa (%esi, %eax), %xmm0 # guardem 16 posicions de la mata
	pand %xmm2, %xmm0 # fem la pand amb les 16 posicions de mata
	pcmpgtb %xmm3, %xmm0 # xmm0 - 0 en cada posicio, posa 255 (true) si la posicio > 0, o 0 al reves
	movdqa %xmm0, (%edx, %eax) # guarda en matb tots els canvis nous

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
