global _ft_strlen
section .text

_ft_strlen:
	mov r12, rdi					; // Argument 1: (char *) s
	mov rcx, 0						; counter = 0
	loop:
		cmp BYTE [r12], 0			; cmp: *s == 0
		jne increment				; if true: goto increment
		je endloop					; if false: goto endloop
	increment:
		inc rcx						; counter++
		inc r12						; s++
		jmp loop					; goto: loop
	endloop:
	mov rax, rcx					; set returned value = counter
	ret								; do return
