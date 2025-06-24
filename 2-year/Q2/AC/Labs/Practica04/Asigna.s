 .text
	.align 4
	.globl Asignar
	.type Asignar,@function
Asignar:
        # Aqui viene vuestro codigo
	pushl %ebp
	movl %esp, %ebp

	imul $12, 24(%ebp), %edx # edx = pos * 12
	addl 8(%ebp), %edx # edx = @v + pos*12

	movl 12(%ebp), %ecx
	movl %ecx, (%edx) #v[pos].c = X.c

	movl 16(%ebp), %ecx
	movl %ecx, 4(%edx) #v[pos].k = X.k

	movl 20(%ebp), %ecx
	movl %ecx, 8(%edx) #v[pos].m = X.m

	movl %ebp, %esp
	popl %ebp
	ret
