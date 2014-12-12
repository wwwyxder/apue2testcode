	.file	"dummy.c"
	.text
.globl dummy
	.type	dummy, @function
dummy:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1234, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	leave
	ret
	.size	dummy, .-dummy
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits
