	.file	"main.c"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "help placeholder\0"
	.text
	.globl	"print_help"
	.def	"print_help";	.scl	2;	.type	32;	.endef
	.seh_proc	"print_help"
"print_help":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	lea	rax, .LC0[rip]
	mov	rcx, rax
	call	"puts"
	nop
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "%hhx%n\0"
	.align 8
.LC2:
	.ascii "Error: -k requires 16 valid hex bytes.\12\0"
.LC3:
	.ascii "getentropy failed\0"
.LC4:
	.ascii "%02X \0"
.LC5:
	.ascii "vtk:h\0"
.LC6:
	.ascii "AES key: \0"
.LC7:
	.ascii "\12--- AES KEY ---\0"
.LC8:
	.ascii "enter your string: \0"
.LC9:
	.ascii "getline failed\0"
.LC10:
	.ascii "malloc failed\0"
.LC11:
	.ascii "realloc failed\0"
.LC12:
	.ascii "\12--- Block %d ---\12\0"
	.text
	.globl	"main"
	.def	"main";	.scl	2;	.type	32;	.endef
	.seh_proc	"main"
"main":
	push	rbp
	.seh_pushreg	rbp
	sub	rsp, 272
	.seh_stackalloc	272
	lea	rbp, 128[rsp]
	.seh_setframe	rbp, 128
	.seh_endprologue
	mov	DWORD PTR 160[rbp], ecx
	mov	QWORD PTR 168[rbp], rdx
	call	"__main"
	mov	BYTE PTR 143[rbp], 0
	mov	BYTE PTR 142[rbp], 0
	mov	BYTE PTR 35[rbp], 0
	jmp	.L3
.L26:
	cmp	DWORD PTR 28[rbp], 118
	je	.L4
	cmp	DWORD PTR 28[rbp], 118
	jg	.L5
	cmp	DWORD PTR 28[rbp], 116
	je	.L6
	cmp	DWORD PTR 28[rbp], 116
	jg	.L5
	cmp	DWORD PTR 28[rbp], 104
	je	.L7
	cmp	DWORD PTR 28[rbp], 107
	je	.L8
	jmp	.L5
.L4:
	mov	BYTE PTR 143[rbp], 1
	jmp	.L3
.L8:
	mov	BYTE PTR 142[rbp], 1
	mov	rax, QWORD PTR __imp_optarg[rip]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR 128[rbp], rax
	mov	DWORD PTR 124[rbp], 0
	jmp	.L9
.L12:
	mov	DWORD PTR -80[rbp], 0
	lea	r8, -80[rbp]
	lea	rcx, -73[rbp]
	lea	rdx, .LC1[rip]
	mov	rax, QWORD PTR 128[rbp]
	mov	r9, r8
	mov	r8, rcx
	mov	rcx, rax
	call	"sscanf"
	cmp	eax, 1
	je	.L10
	call	"__getreent"
	mov	rdx, QWORD PTR 24[rax]
	lea	rax, .LC2[rip]
	mov	r9, rdx
	mov	r8d, 39
	mov	edx, 1
	mov	rcx, rax
	call	"fwrite"
	mov	eax, 0
	jmp	.L59
.L10:
	movzx	edx, BYTE PTR -73[rbp]
	mov	eax, DWORD PTR 124[rbp]
	cdqe
	mov	BYTE PTR -48[rbp+rax], dl
	mov	eax, DWORD PTR -80[rbp]
	cdqe
	add	QWORD PTR 128[rbp], rax
	add	DWORD PTR 124[rbp], 1
.L9:
	cmp	DWORD PTR 124[rbp], 15
	jle	.L12
	jmp	.L3
.L7:
	call	"print_help"
	mov	eax, 1
	jmp	.L59
.L6:
	mov	BYTE PTR 35[rbp], 1
	mov	DWORD PTR -12[rbp], 2
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	sal	rax, 4
	mov	rcx, rax
	call	"malloc"
	mov	QWORD PTR -24[rbp], rax
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -24[rbp]
	mov	rcx, rax
	call	"getentropy"
	test	eax, eax
	je	.L13
	lea	rax, .LC3[rip]
	mov	rcx, rax
	call	"perror"
	mov	eax, 1
	jmp	.L59
.L13:
	mov	DWORD PTR 120[rbp], 0
	jmp	.L14
.L19:
	mov	DWORD PTR 116[rbp], 0
	jmp	.L15
.L18:
	mov	DWORD PTR 112[rbp], 0
	jmp	.L16
.L17:
	mov	eax, DWORD PTR 120[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -24[rbp]
	lea	rcx, [rdx+rax]
	mov	eax, DWORD PTR 112[rbp]
	movsxd	rdx, eax
	mov	eax, DWORD PTR 116[rbp]
	cdqe
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	lea	rcx, .LC4[rip]
	mov	edx, eax
	call	"printf"
	add	DWORD PTR 112[rbp], 1
.L16:
	cmp	DWORD PTR 112[rbp], 3
	jle	.L17
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 116[rbp], 1
.L15:
	cmp	DWORD PTR 116[rbp], 3
	jle	.L18
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 120[rbp], 1
.L14:
	mov	eax, DWORD PTR 120[rbp]
	cmp	eax, DWORD PTR -12[rbp]
	jl	.L19
	mov	edx, DWORD PTR -12[rbp]
	mov	rax, QWORD PTR -24[rbp]
	mov	rcx, rax
	call	"shift_rows"
	mov	DWORD PTR 108[rbp], 0
	jmp	.L20
.L25:
	mov	DWORD PTR 104[rbp], 0
	jmp	.L21
.L24:
	mov	DWORD PTR 100[rbp], 0
	jmp	.L22
.L23:
	mov	eax, DWORD PTR 108[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -24[rbp]
	lea	rcx, [rdx+rax]
	mov	eax, DWORD PTR 100[rbp]
	movsxd	rdx, eax
	mov	eax, DWORD PTR 104[rbp]
	cdqe
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	lea	rcx, .LC4[rip]
	mov	edx, eax
	call	"printf"
	add	DWORD PTR 100[rbp], 1
.L22:
	cmp	DWORD PTR 100[rbp], 3
	jle	.L23
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 104[rbp], 1
.L21:
	cmp	DWORD PTR 104[rbp], 3
	jle	.L24
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 108[rbp], 1
.L20:
	mov	eax, DWORD PTR 108[rbp]
	cmp	eax, DWORD PTR -12[rbp]
	jl	.L25
	mov	eax, 0
	jmp	.L59
.L5:
	call	"print_help"
	mov	eax, 1
	jmp	.L59
.L3:
	lea	rcx, .LC5[rip]
	mov	rdx, QWORD PTR 168[rbp]
	mov	eax, DWORD PTR 160[rbp]
	mov	r8, rcx
	mov	ecx, eax
	call	"getopt"
	mov	DWORD PTR 28[rbp], eax
	cmp	DWORD PTR 28[rbp], -1
	jne	.L26
	movzx	eax, BYTE PTR 142[rbp]
	xor	eax, 1
	test	al, al
	je	.L27
	lea	rax, -48[rbp]
	mov	edx, 16
	mov	rcx, rax
	call	"getentropy"
	test	eax, eax
	je	.L28
	lea	rax, .LC3[rip]
	mov	rcx, rax
	call	"perror"
	mov	eax, 1
	jmp	.L59
.L28:
	cmp	BYTE PTR 143[rbp], 0
	je	.L27
	lea	rax, .LC6[rip]
	mov	rcx, rax
	call	"printf"
	mov	DWORD PTR 96[rbp], 0
	jmp	.L29
.L30:
	mov	eax, DWORD PTR 96[rbp]
	cdqe
	movzx	eax, BYTE PTR -48[rbp+rax]
	movzx	eax, al
	lea	rcx, .LC4[rip]
	mov	edx, eax
	call	"printf"
	add	DWORD PTR 96[rbp], 1
.L29:
	cmp	DWORD PTR 96[rbp], 15
	jle	.L30
	call	"__getreent"
	mov	rax, QWORD PTR 16[rax]
	mov	rcx, rax
	call	"fflush"
	mov	ecx, 10
	call	"putchar"
.L27:
	mov	DWORD PTR 92[rbp], 0
	jmp	.L31
.L32:
	mov	edx, DWORD PTR 92[rbp]
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	ecx, edx
	mov	eax, DWORD PTR 92[rbp]
	lea	edx, 3[rax]
	test	eax, eax
	cmovs	eax, edx
	sar	eax, 2
	mov	edx, eax
	mov	eax, DWORD PTR 92[rbp]
	cdqe
	movzx	eax, BYTE PTR -48[rbp+rax]
	movsxd	rdx, edx
	movsxd	rcx, ecx
	sal	rcx, 2
	lea	rcx, 144[rcx]
	add	rcx, rbp
	add	rdx, rcx
	sub	rdx, 208
	mov	BYTE PTR [rdx], al
	add	DWORD PTR 92[rbp], 1
.L31:
	cmp	DWORD PTR 92[rbp], 15
	jle	.L32
	cmp	BYTE PTR 143[rbp], 0
	je	.L33
	lea	rax, .LC7[rip]
	mov	rcx, rax
	call	"puts"
	mov	DWORD PTR 88[rbp], 0
	jmp	.L34
.L37:
	mov	DWORD PTR 84[rbp], 0
	jmp	.L35
.L36:
	mov	eax, DWORD PTR 84[rbp]
	cdqe
	mov	edx, DWORD PTR 88[rbp]
	movsxd	rdx, edx
	sal	rdx, 2
	lea	rcx, 144[rdx]
	lea	rdx, [rcx+rbp]
	add	rax, rdx
	sub	rax, 208
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	lea	rcx, .LC4[rip]
	mov	edx, eax
	call	"printf"
	add	DWORD PTR 84[rbp], 1
.L35:
	cmp	DWORD PTR 84[rbp], 3
	jle	.L36
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 88[rbp], 1
.L34:
	cmp	DWORD PTR 88[rbp], 3
	jle	.L37
.L33:
	mov	QWORD PTR -72[rbp], 0
	mov	QWORD PTR 72[rbp], 0
	mov	ecx, 0
	call	"isatty"
	test	eax, eax
	je	.L38
	lea	rax, .LC8[rip]
	mov	rcx, rax
	call	"printf"
	call	"__getreent"
	mov	rax, QWORD PTR 16[rax]
	mov	rcx, rax
	call	"fflush"
	mov	QWORD PTR -88[rbp], 0
	call	"__getreent"
	mov	rcx, QWORD PTR 8[rax]
	lea	rdx, -88[rbp]
	lea	rax, -72[rbp]
	mov	r8, rcx
	mov	rcx, rax
	call	"getline"
	mov	QWORD PTR 72[rbp], rax
	cmp	QWORD PTR 72[rbp], -1
	jne	.L40
	lea	rax, .LC9[rip]
	mov	rcx, rax
	call	"perror"
	mov	eax, 1
	jmp	.L59
.L38:
	mov	QWORD PTR 64[rbp], 4096
	mov	rax, QWORD PTR 64[rbp]
	mov	rcx, rax
	call	"malloc"
	mov	QWORD PTR -72[rbp], rax
	mov	rax, QWORD PTR -72[rbp]
	test	rax, rax
	jne	.L41
	lea	rax, .LC10[rip]
	mov	rcx, rax
	call	"perror"
	mov	eax, 1
	jmp	.L59
.L41:
	mov	QWORD PTR 56[rbp], 0
	mov	QWORD PTR 16[rbp], 0
.L46:
	mov	rax, QWORD PTR 56[rbp]
	add	rax, 1
	cmp	rax, QWORD PTR 64[rbp]
	jb	.L42
	sal	QWORD PTR 64[rbp]
	mov	rax, QWORD PTR -72[rbp]
	mov	rdx, QWORD PTR 64[rbp]
	mov	rcx, rax
	call	"realloc"
	mov	QWORD PTR 8[rbp], rax
	cmp	QWORD PTR 8[rbp], 0
	jne	.L43
	lea	rax, .LC11[rip]
	mov	rcx, rax
	call	"perror"
	mov	rax, QWORD PTR -72[rbp]
	mov	rcx, rax
	call	"free"
	mov	eax, 1
	jmp	.L59
.L43:
	mov	rax, QWORD PTR 8[rbp]
	mov	QWORD PTR -72[rbp], rax
.L42:
	call	"__getreent"
	mov	rcx, QWORD PTR 8[rax]
	mov	rax, QWORD PTR 64[rbp]
	sub	rax, QWORD PTR 56[rbp]
	lea	r8, -1[rax]
	mov	rdx, QWORD PTR -72[rbp]
	mov	rax, QWORD PTR 56[rbp]
	add	rax, rdx
	mov	r9, rcx
	mov	edx, 1
	mov	rcx, rax
	call	"fread"
	mov	QWORD PTR 16[rbp], rax
	cmp	QWORD PTR 16[rbp], 0
	je	.L61
	mov	rax, QWORD PTR 16[rbp]
	add	QWORD PTR 56[rbp], rax
	jmp	.L46
.L61:
	nop
	mov	rdx, QWORD PTR -72[rbp]
	mov	rax, QWORD PTR 56[rbp]
	add	rax, rdx
	mov	BYTE PTR [rax], 0
	mov	rax, QWORD PTR 56[rbp]
	mov	QWORD PTR 72[rbp], rax
.L40:
	mov	rdx, QWORD PTR 72[rbp]
	mov	rax, rdx
	sar	rax, 63
	shr	rax, 60
	add	rdx, rax
	and	edx, 15
	sub	rdx, rax
	mov	rax, rdx
	mov	edx, eax
	mov	eax, 16
	sub	eax, edx
	mov	DWORD PTR 4[rbp], eax
	mov	rax, QWORD PTR 72[rbp]
	lea	rdx, 15[rax]
	test	rax, rax
	cmovs	rax, rdx
	sar	rax, 4
	add	eax, 1
	mov	DWORD PTR 0[rbp], eax
	mov	eax, DWORD PTR 0[rbp]
	cdqe
	sal	rax, 4
	mov	rcx, rax
	call	"malloc"
	mov	QWORD PTR -8[rbp], rax
	mov	DWORD PTR 52[rbp], 0
	jmp	.L47
.L52:
	mov	DWORD PTR 48[rbp], 0
	jmp	.L48
.L51:
	mov	eax, DWORD PTR 52[rbp]
	sal	eax, 4
	mov	edx, eax
	mov	eax, DWORD PTR 48[rbp]
	add	eax, edx
	cdqe
	cmp	QWORD PTR 72[rbp], rax
	jle	.L49
	mov	rdx, QWORD PTR -72[rbp]
	mov	eax, DWORD PTR 52[rbp]
	sal	eax, 4
	mov	ecx, eax
	mov	eax, DWORD PTR 48[rbp]
	add	eax, ecx
	cdqe
	add	rax, rdx
	movzx	r8d, BYTE PTR [rax]
	mov	eax, DWORD PTR 52[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	lea	rcx, [rdx+rax]
	mov	edx, DWORD PTR 48[rbp]
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	r9d, edx
	mov	eax, DWORD PTR 48[rbp]
	lea	edx, 3[rax]
	test	eax, eax
	cmovs	eax, edx
	sar	eax, 2
	movsxd	rdx, eax
	movsxd	rax, r9d
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	mov	BYTE PTR [rax], r8b
	jmp	.L50
.L49:
	mov	eax, DWORD PTR 52[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	lea	rcx, [rdx+rax]
	mov	edx, DWORD PTR 48[rbp]
	mov	eax, edx
	sar	eax, 31
	shr	eax, 30
	add	edx, eax
	and	edx, 3
	sub	edx, eax
	mov	r9d, edx
	mov	eax, DWORD PTR 48[rbp]
	lea	edx, 3[rax]
	test	eax, eax
	cmovs	eax, edx
	sar	eax, 2
	mov	edx, eax
	mov	eax, DWORD PTR 4[rbp]
	mov	r8d, eax
	movsxd	rdx, edx
	movsxd	rax, r9d
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	mov	BYTE PTR [rax], r8b
.L50:
	add	DWORD PTR 48[rbp], 1
.L48:
	cmp	DWORD PTR 48[rbp], 15
	jle	.L51
	add	DWORD PTR 52[rbp], 1
.L47:
	mov	eax, DWORD PTR 52[rbp]
	cmp	eax, DWORD PTR 0[rbp]
	jl	.L52
	mov	DWORD PTR 44[rbp], 0
	jmp	.L53
.L58:
	mov	eax, DWORD PTR 44[rbp]
	lea	rcx, .LC12[rip]
	mov	edx, eax
	call	"printf"
	mov	DWORD PTR 40[rbp], 0
	jmp	.L54
.L57:
	mov	DWORD PTR 36[rbp], 0
	jmp	.L55
.L56:
	mov	eax, DWORD PTR 44[rbp]
	cdqe
	sal	rax, 4
	mov	rdx, rax
	mov	rax, QWORD PTR -8[rbp]
	lea	rcx, [rdx+rax]
	mov	eax, DWORD PTR 36[rbp]
	movsxd	rdx, eax
	mov	eax, DWORD PTR 40[rbp]
	cdqe
	sal	rax, 2
	add	rax, rcx
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movzx	eax, al
	lea	rcx, .LC4[rip]
	mov	edx, eax
	call	"printf"
	add	DWORD PTR 36[rbp], 1
.L55:
	cmp	DWORD PTR 36[rbp], 3
	jle	.L56
	mov	ecx, 10
	call	"putchar"
	add	DWORD PTR 40[rbp], 1
.L54:
	cmp	DWORD PTR 40[rbp], 3
	jle	.L57
	add	DWORD PTR 44[rbp], 1
.L53:
	mov	eax, DWORD PTR 44[rbp]
	cmp	eax, DWORD PTR 0[rbp]
	jl	.L58
	call	"__getreent"
	mov	rax, QWORD PTR 16[rax]
	mov	rcx, rax
	call	"fflush"
	mov	rax, QWORD PTR -8[rbp]
	mov	rcx, rax
	call	"free"
	mov	rax, QWORD PTR -72[rbp]
	mov	rcx, rax
	call	"free"
	mov	eax, 0
.L59:
	add	rsp, 272
	pop	rbp
	ret
	.seh_endproc
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (GNU) 16.2.0"
	.def	"puts";	.scl	2;	.type	32;	.endef
	.def	"sscanf";	.scl	2;	.type	32;	.endef
	.def	"__getreent";	.scl	2;	.type	32;	.endef
	.def	"fwrite";	.scl	2;	.type	32;	.endef
	.def	"malloc";	.scl	2;	.type	32;	.endef
	.def	"getentropy";	.scl	2;	.type	32;	.endef
	.def	"perror";	.scl	2;	.type	32;	.endef
	.def	"printf";	.scl	2;	.type	32;	.endef
	.def	"putchar";	.scl	2;	.type	32;	.endef
	.def	"shift_rows";	.scl	2;	.type	32;	.endef
	.def	"getopt";	.scl	2;	.type	32;	.endef
	.def	"fflush";	.scl	2;	.type	32;	.endef
	.def	"puts";	.scl	2;	.type	32;	.endef
	.def	"putchar";	.scl	2;	.type	32;	.endef
	.def	"isatty";	.scl	2;	.type	32;	.endef
	.def	"getline";	.scl	2;	.type	32;	.endef
	.def	"realloc";	.scl	2;	.type	32;	.endef
	.def	"free";	.scl	2;	.type	32;	.endef
	.def	"fread";	.scl	2;	.type	32;	.endef
