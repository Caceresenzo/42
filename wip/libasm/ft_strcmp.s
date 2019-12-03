global _ft_strcmp
section .text

_ft_strcmp:
	mov r12, rdi					; // Argument 1: (const char *) s1
	mov r13, rsi					; // Argument 2: (const char *) s2

	loop:
		cmp BYTE [r12], 0			; cmp: *s1 == 0
		je endloop					; if true: goto endloop
		jne check_diff				; if false: goto check_diff

	check_diff:
		mov r8b, [r12]				; current = *s1
		cmp r8b, [r13]				; cmp: current == *s2
		je increment				; if true: goto increment
		jne endloop					; if false: goto endloop

	increment:
		inc r12						; s1++
		inc r13						; s2++
		jmp loop					; goto: loop

	endloop:
		;

	mov r8b, [r12]					; current1 = *s1
	mov r9b, [r13]					; current2 = *s2
	sub r8b, r9b					; diff = current1 - current2
	movsx rax, r8b					; set returned value = diff (mov byte with sign)

	ret								; do return