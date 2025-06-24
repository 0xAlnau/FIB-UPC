.text
	.align 4
	.globl procesar
	.type procesar, @function
procesar:
	pushl %ebp
	movl %esp, %ebp
	subl $16, %esp
	pushl %ebx
	pushl %esi
	pushl %edi

# Aqui has de introducir el codigo
	#tratare les matrius com si fosin un vector de mida n*n
	movl $0, %eax # i = 0

	movl 16(%ebp), %edi  # edi = n
	imul %edi, %edi # edi = n*n

	movl 8(%ebp), %esi # esi = @mata
	movl 12(%ebp), %edx # edx = @matb
for:
	cmpl %edi, %eax # i - n*n
	jge fi_for

	movb (%esi,%eax), %bl # bl = mata[i] (@ini + i*1)

	movb (%edx,%eax), %cl # cl = matb[i] (@ini + i*1)

	andb $1, %bl # bl = mata & 1
	movb %bl, %cl # cl = mata & 1

	cmpb $0, %cl # matb - 0
	jle else
if:
	movb $255, %cl
	jmp fi_if
else:
	movb $0, %cl
fi_if:
	movb %cl, (%edx,%eax) # matb[i] = matb

	incl %eax # ++i
	jmp for
fi_for:


# El final de la rutina ya esta programado

	popl %edi
	popl %esi
	popl %ebx
	movl %ebp,%esp
	popl %ebp
	ret
