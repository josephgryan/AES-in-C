	.file	"aes.c"
	.intel_syntax noprefix
	.text
	.globl	"sub_bytes"
	.def	"sub_bytes";	.scl	2;	.type	32;	.endef
	.seh_proc	"sub_bytes"
"sub_bytes":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	nop
	pop	rbp
	ret
	.seh_endproc
	.globl	"shift_rows"
	.def	"shift_rows";	.scl	2;	.type	32;	.endef
	.seh_proc	"shift_rows"
"shift_rows":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	DWORD PTR 24[rbp], edx
	mov	DWORD PTR -4[rbp], 0
	jmp	.L3
.L10:
	mov	DWORD PTR -8[rbp], 0
	jmp	.L4
.L9:
	mov	DWORD PTR -12[rbp], 0
	jmp	.L5
.L6:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR 16[rbp]
	lea	rcx, [rdx+rax]
	mov	edx, DWORD PTR -12[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	eax, edx
	movsxd	rdx, eax
	mov	eax, DWORD PTR -8[rbp]
	cdqe
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	movzx	edx, BYTE PTR [rax]
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	mov	BYTE PTR -20[rbp+rax], dl
	add	DWORD PTR -12[rbp], 1
.L5:
	cmp	DWORD PTR -12[rbp], 3
	jle	.L6
	mov	DWORD PTR -16[rbp], 0
	jmp	.L7
.L8:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR 16[rbp]
	lea	r8, [rdx+rax]
	mov	eax, DWORD PTR -16[rbp]
	cdqe
	movzx	edx, BYTE PTR -20[rbp+rax]
	mov	eax, DWORD PTR -16[rbp]
	movsxd	rcx, eax
	mov	eax, DWORD PTR -8[rbp]
	cdqe
	sal	rax, 2
	add	rax, r8
	add	rax, rcx
	mov	BYTE PTR [rax], dl
	add	DWORD PTR -16[rbp], 1
.L7:
	cmp	DWORD PTR -16[rbp], 3
	jle	.L8
	add	DWORD PTR -8[rbp], 1
.L4:
	cmp	DWORD PTR -8[rbp], 3
	jle	.L9
	add	DWORD PTR -4[rbp], 1
.L3:
	mov	eax, DWORD PTR -4[rbp]
	cmp	eax, DWORD PTR 24[rbp]
	jl	.L10
	nop
	nop
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.globl	"mix_columns"
	.def	"mix_columns";	.scl	2;	.type	32;	.endef
	.seh_proc	"mix_columns"
"mix_columns":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	nop
	pop	rbp
	ret
	.seh_endproc
	.globl	"add_round_key"
	.def	"add_round_key";	.scl	2;	.type	32;	.endef
	.seh_proc	"add_round_key"
"add_round_key":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	nop
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 16.2.0"
