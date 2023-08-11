	.file	"hook.c"
	.text
	.type	adjust_protect_memory_permissions, @function
adjust_protect_memory_permissions:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	cmpl	$0, -16(%rbp)
	jg	.L2
	call	getpagesize@PLT
	movl	%eax, -16(%rbp)
.L2:
	movl	-16(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	negl	%edx
	movslq	%edx, %rcx
	movq	-8(%rbp), %rdx
	andq	%rcx, %rdx
	movq	%rdx, %rcx
	movl	-12(%rbp), %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	mprotect@PLT
	testl	%eax, %eax
	jns	.L3
	movl	$-1, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	adjust_protect_memory_permissions, .-adjust_protect_memory_permissions
	.globl	install_hook
	.type	install_hook, @function
install_hook:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L6
	cmpq	$0, -48(%rbp)
	jne	.L7
.L6:
	movl	$0, %eax
	jmp	.L8
.L7:
	call	getpagesize@PLT
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	testl	%eax, %eax
	jns	.L9
	movl	$0, %eax
	jmp	.L8
.L9:
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$5, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L10
	movl	$0, %eax
	jmp	.L8
.L10:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	movl	1(%rax), %eax
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	leaq	5(%rax), %rdx
	movq	-16(%rbp), %rax
	subq	%rdx, %rax
	movl	%eax, -28(%rbp)
	movq	-24(%rbp), %rax
	movb	$-23, (%rax)
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-32(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	movq	-8(%rbp), %rax
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	install_hook, .-install_hook
	.globl	uninstall_hook
	.type	uninstall_hook, @function
uninstall_hook:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L12
	cmpq	$0, -48(%rbp)
	jne	.L13
.L12:
	movl	$-1, %eax
	jmp	.L14
.L13:
	call	getpagesize@PLT
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	testl	%eax, %eax
	jns	.L15
	movl	$-1, %eax
	jmp	.L14
.L15:
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-16(%rbp), %rax
	movb	%dl, (%rax)
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	1(%rax), %eax
	movl	%eax, (%rdx)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	$0, -48(%rbp)
	movl	-20(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	movl	$0, %eax
.L14:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	uninstall_hook, .-uninstall_hook
	.globl	hook
	.type	hook, @function
hook:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	call	getpagesize@PLT
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %edx
	movq	-64(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	testl	%eax, %eax
	jns	.L17
	movl	$-1, %eax
	jmp	.L18
.L17:
	movq	-56(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L19
	cmpq	$0, -24(%rbp)
	je	.L19
	cmpq	$0, -16(%rbp)
	jne	.L20
.L19:
	movl	$-1, %eax
	jmp	.L18
.L20:
	movl	$0, -48(%rbp)
	jmp	.L21
.L23:
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$-24, %al
	jne	.L22
	movq	-32(%rbp), %rax
	movl	1(%rax), %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	cltq
	leaq	5(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jne	.L22
	movq	-32(%rbp), %rax
	leaq	5(%rax), %rdx
	movq	-16(%rbp), %rax
	subq	%rdx, %rax
	movl	%eax, -36(%rbp)
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rdx
	movl	-36(%rbp), %eax
	movl	%eax, (%rdx)
.L22:
	addl	$1, -48(%rbp)
	addq	$1, -32(%rbp)
.L21:
	movl	-48(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L23
	movl	-44(%rbp), %edx
	movq	-56(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	adjust_protect_memory_permissions
	movl	$0, %eax
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	hook, .-hook
	.globl	unhook
	.type	unhook, @function
unhook:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	hook
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	unhook, .-unhook
	.section	.rodata
.LC0:
	.string	"%s: %d\n"
	.text
	.globl	test
	.type	test, @function
test:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	__FUNCTION__.1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	test, .-test
	.globl	test_hooker
	.type	test_hooker, @function
test_hooker:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	__FUNCTION__.0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	test_hooker, .-test_hooker
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	leaq	test_hooker(%rip), %rax
	movq	%rax, %rsi
	leaq	test(%rip), %rax
	movq	%rax, %rdi
	call	install_hook
	movq	%rax, -8(%rbp)
	movl	$0, %edi
	call	test
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	test(%rip), %rax
	movq	%rax, %rdi
	call	uninstall_hook
	movl	$0, %edi
	call	test
	leaq	test_hooker(%rip), %rax
	movq	%rax, %rdx
	leaq	test(%rip), %rax
	movq	%rax, %rsi
	leaq	main(%rip), %rax
	movq	%rax, %rdi
	call	hook
	movl	$1, %edi
	call	test
	leaq	test_hooker(%rip), %rax
	movq	%rax, %rdx
	leaq	test(%rip), %rax
	movq	%rax, %rsi
	leaq	main(%rip), %rax
	movq	%rax, %rdi
	call	unhook
	movl	$1, %edi
	call	test
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.section	.rodata
	.type	__FUNCTION__.1, @object
	.size	__FUNCTION__.1, 5
__FUNCTION__.1:
	.string	"test"
	.align 8
	.type	__FUNCTION__.0, @object
	.size	__FUNCTION__.0, 12
__FUNCTION__.0:
	.string	"test_hooker"
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
