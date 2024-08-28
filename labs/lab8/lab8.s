	.file	"lab8.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$8, -16(%rbp)
	movl	$33, -12(%rbp)
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	cmpl	%eax, %edx
	cmovle	%edx, %eax
	movl	%eax, %edi
	call	foo@PLT
	movl	%eax, -8(%rbp)
	movss	.LC0(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1105599660
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
