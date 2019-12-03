global _ft_strcpy
section .text

_ft_strcpy:
	mov r12, rdi					; // Argument 1: (char *) dst
	mov r13, rsi					; // Argument 2: (const char *) src
	mov rax, r12					; set returned value = dst
	loop:
		cmp BYTE [r13], 0			; cmp: *src == 0
		je endloop					; if true: goto endloop
		jne copy					; if false: goto copy
	copy:
		mov r13, r12				; *dst = *src
		inc r12						; dst++
		inc r13						; src++
		jmp loop					; goto: loop
	endloop:
		mov r13, 0					; *dst = '\0'
	ret								; do return
