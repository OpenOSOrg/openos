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
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
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
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	xorl	%r15d, %r15d
	call	strtol@PLT
	movq	16(%rbx), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	movq	%rax, %r14
	call	strtol@PLT
	movl	%r14d, %edx
	movl	$1, %edi
	leaq	.LC1(%rip), %rsi
	movq	$0, shared_counter(%rip)
	movslq	%eax, %r12
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%r14, 8(%rsp)
	movslq	8(%rsp), %rdi
	salq	$3, %rdi
	call	malloc@PLT
	movl	$2, %ecx
	movq	%rax, %rbp
	movl	%r14d, %eax
	leaq	increment_thread(%rip), %r14
	cltd
	movq	%rbp, %rbx
	idivl	%ecx
	cmpl	$1, 8(%rsp)
	movl	%eax, %r13d
	jle	.L16
	.p2align 4,,10
	.p2align 3
.L14:
	movq	%rbx, %rdi
	movq	%r12, %rcx
	movq	%r14, %rdx
	xorl	%esi, %esi
	call	pthread_create@PLT
	addq	$8, %rbx
	movq	%r12, %rcx
	xorl	%esi, %esi
	leaq	decrement_thread(%rip), %rdx
	movq	%rbx, %rdi
	addl	$1, %r15d
	call	pthread_create@PLT
	cmpl	%r13d, %r15d
	jl	.L14
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L15:
	movq	0(%rbp,%rbx,8), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movq	8(%rbp,%rbx,8), %rdi
	xorl	%esi, %esi
	addq	$1, %rbx
	call	pthread_join@PLT
	cmpl	%ebx, %r13d
	jg	.L15
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
