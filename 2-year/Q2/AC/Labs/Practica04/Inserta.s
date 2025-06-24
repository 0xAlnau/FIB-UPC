.text
	.align 4
	.globl Insertar
	.type Insertar,@function
Insertar:
        # Aqui viene vuestro codigo
	pushl %ebp
	movl %esp, %ebp
	subl $12, %esp
	pushl %esi
	pushl %edi

	movl $0, -12(%ebp) # i = 0
	movl $-1, -4(%ebp) # lug = -1

do:
	movl 16(%ebp), %esi # esi = X.k
	imul $12, -12(%ebp), %edi # edi = 12 * i
	addl 8(%ebp), %edi #edi = @v + 12*i
	movl 4(%edi), %edi # edi = v[i].k

	cmpl %edi, %esi
	jge else
if:
	movl -12(%ebp), %esi # esi = i
	movl %esi, -4(%ebp) #lug = i
	jmp end_do_while1
else:
	incl -12(%ebp) #i++
	imul $12, -12(%ebp), %edi # edi = 12 * i
	addl 8(%ebp), %edi #edi = @v + 12*i
	movl 4(%edi), %edi # edi = v[i].k
	cmpl 0x80000000, %edi # v[i].k - 0x80000000
	je end_do_while1
	jmp do
end_do_while1:
	cmpl 0x80000000, %edi # v[i].k - 0x80000000
	jne else2
if2:
	movl -12(%ebp), %esi # esi = i
	movl %esi, -4(%ebp) #lug = i
	jmp fi_if
else2:
while:
	imul $12, -12(%ebp), %edi # edi = 12 * i
	addl 8(%ebp), %edi #edi = @v + 12*i
	movl 4(%edi), %edi # edi = v[i].k
	cmpl 0x80000000, %edi # v[i].k - 0x80000000
	je end_while
	incl -12(%ebp)
	jmp while
end_while:
fi_if:
	movl -12(%ebp), %esi
	movl %esi,-8(%ebp) # j = i
	movl -4(%ebp), %esi # esi = lug
for:
	cmpl %esi, -8(%ebp) # j - lug
	jl fi_for
	imul $12, -8(%ebp), %ecx # 12 * j
	addl 8(%ebp), %ecx # @v + 12*j
	incl -8(%ebp) # j++
	imul $12, -8(%ebp), %edx # 12 * j+1
	addl 8(%ebp), %edx # @v + 12*j+1
	decl -8(%ebp) # j--

	movl (%ecx), %eax
	movl %eax, (%edx) # v[j+1].c = v[j].c

	movl 4(%ecx), %eax
	movl %eax, 4(%edx) # v[j+1].k = v[j].k

	movl 8(%ecx), %eax
	movl %eax, 8(%edx) # v[j+1].m = v[j].m

	decl -8(%ebp)
	jmp for
fi_for:
	pushl -4(%ebp) # lug
	pushl 12(%ebp) # X
	pushl 8(%ebp) # v
	call Asignar
	addl $12, %esp
	movl -12(%ebp), %eax
	incl %eax

	popl %edi
	popl %esi
	movl %ebp, %esp
	popl %ebp
	ret
