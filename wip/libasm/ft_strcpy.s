global _ft_strcpy

extern _notify
extern _notifys

section .text

_ft_strcpy:
	push r12
	push r13
	push r14
	
	mov r12, rdi					; // Argument 1: (char *) dst
	mov r13, rsi					; // Argument 2: (const char *) src

	mov r14, r12					; start = dst
	loop:
		
		cmp r13b, 0					; cmp: (unsigned char)*src == 0
		jne copy					; if false: goto copy
		je endloop					; if true: goto endloop

	copy:
		mov rsi, r13				; mov: source = src
		mov rdi, r12				; mov: destination = dst
		movsb						; move string byte: *source = *destination
		inc r12						; dst++
		inc r13						; src++
		jmp loop					; goto: loop

	endloop:
		mov r13, 0					; *dst = '\0'

	mov rax, r14					; set returned value = start

	pop r14
	pop r13
	pop r12
	
	ret								; do return
