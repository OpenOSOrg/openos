	.file	"counter.c"
	.text
	.p2align 4
	.type	increment_thread, @function
increment_thread:
.LFB62:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	jle	.L2
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L3:
	movq	shared_counter(%rip), %rax
	addq	$1, %rdx
	addq	$1, %rax
	movq	%rax, shared_counter(%rip)
	cmpq	%rdx, %rdi
	jne	.L3
.L2:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE62:
	.size	increment_thread, .-increment_thread
	.p2align 4
	.type	decrement_thread, @function
decrement_thread:
.LFB63:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	jle	.L7
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L8:
	movq	shared_counter(%rip), %rax
	addq	$1, %rdx
	subq	$1, %rax
	movq	%rax, shared_counter(%rip)
	cmpq	%rdx, %rdi
	jne	.L8
.L7:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE63:
	.size	decrement_thread, .-decrement_thread
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Usage: %s <num_threads> <num_iters>\n"
	.align 8
.LC1:
	.string	"Main thread: Beginning test with %d threads\n"
	.align 8
.LC2:
	.string	"Main thread: Final value of shared counter is %ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB64:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	cmpl	$3, %edi
	je	.L11
	movq	(%rsi), %rcx
	movq	stderr(%rip), %rdi
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rdx
	call	__fprintf_chk@PLT
	movl	$1, %eax
.L10:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	16(%rbx), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	movq	%rax, %rbp
	call	strtol@PLT
	movl	$1, %edi
	movl	%ebp, %edx
	leaq	.LC1(%rip), %rsi
	movq	$0, shared_counter(%rip)
	movslq	%eax, %r12
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movslq	%ebp, %rdi
	salq	$3, %rdi
	call	malloc@PLT
	testl	%ebp, %ebp
	jle	.L16
	subl	$1, %ebp
	movq	%rax, %rbx
	leaq	increment_thread(%rip), %r14
	shrl	%ebp
	salq	$4, %rbp
	leaq	16(%rax,%rbp), %r13
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L14:
	movq	%rbp, %rdi
	movq	%r12, %rcx
	movq	%r14, %rdx
	xorl	%esi, %esi
	call	pthread_create@PLT
	leaq	8(%rbp), %rdi
	movq	%r12, %rcx
	xorl	%esi, %esi
	leaq	decrement_thread(%rip), %rdx
	addq	$16, %rbp
	call	pthread_create@PLT
	cmpq	%r13, %rbp
	jne	.L14
	.p2align 4,,10
	.p2align 3
.L15:
	movq	(%rbx), %rdi
	xorl	%esi, %esi
	addq	$16, %rbx
	call	pthread_join@PLT
	movq	-8(%rbx), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	cmpq	%r13, %rbx
	jne	.L15
.L16:
	movq	shared_counter(%rip), %rdx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L10
	.cfi_endproc
.LFE64:
	.size	main, .-main
	.comm	shared_counter,8,8
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
