.text
	.align 4
	.globl OperaVec
	.type	OperaVec, @function
OperaVec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
# Aqui has de introducir el codigo

	movl $1, -8(%ebp) # i = 1
	movl 12(%ebp), %eax # eax = elementos
	movl 8(%ebp), %ebx # ebx = @ini vector
for:
	cmpl %eax, -8(%ebp) #i - elementos
	jge end_for
	movl -8(%ebp), %ecx #ecx = i
	movl (%ebx, %ecx, 4), %edx # edx = Vector[i]
	decl %ecx
	cmpl (%ebx, %ecx, 4), %edx # Vector[i] - Vector[i-1]
	jne else
if:
	incl %ecx # i
	movl %ecx, -4(%ebp) # res = i
else:
	incl -8(%ebp) # i++
	jmp for
end_for:

# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
