.text
	.align 4
	.globl OperaMat
	.type	OperaMat, @function
OperaMat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
# Aqui has de introducir el codigo

	movl $0, -4(%ebp) # res = 0
	movl 12(%ebp), %eax # eax = salto
	movl 8(%ebp), %ebx # ebx = @ini
	#for 1
	movl $0, -8(%ebp) # i = 0
for1:
	cmpl $3, -8(%ebp) # i - 3
	jge end_for1
	#for2
	movl $0, -12(%ebp) # j = 0
	movl -8(%ebp), %edi # edi = i
for2:
	cmpl %edi, -12(%ebp) # j - i
	jg end_for2
	imul $3, %edi, %ecx # ecx = N * i
	addl -12(%ebp), %ecx # ecx = N* i + j
	movl (%ebx, %ecx, 4), %ecx # ecx = Matriz[i][j]
	addl %ecx, -4(%ebp)
	incl -12(%ebp)
	jmp for2
end_for2:
	addl %eax, -8(%ebp) # i += salto
	jmp for1
end_for1:

# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx	
	movl %ebp,%esp
	popl %ebp
	ret
