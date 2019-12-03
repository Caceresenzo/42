global _ft_strlen
section .text

_ft_strlen:
	mov r12, rdi					; // Argument 1: (char *) s
	mov rax, 0						; set returned value = 0
	loop:
		cmp BYTE [r12], 0			; cmp: *s == 0
		je endloop					; if true: goto endloop
		jne increment				; if false: goto increment
	increment:
		inc rax						; returned value++
		inc r12						; s++
		jmp loop					; goto: loop
	endloop:
	ret								; do return
