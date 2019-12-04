global _ft_strdup

extern _malloc
extern _ft_strlen
extern _ft_strcpy

section .text

_ft_strdup:
	push r12
	push r13
	push r14
	
	mov r12, rdi					; // Argument 1: (const char *) s1

	mov rdi, r12					; passing parameter: s
	call _ft_strlen					; calling ft_strlen
	mov r13, rax					; storing result as "length"
	inc r13							; length++
	imul r13, r13, 1				; length *= sizeof(char)

	mov rdi, r13					; passing parameter: size = length
	call _malloc					; calling malloc
	mov r14, rax					; storing result as "duplicated"
	
	cmp r14, 0						; cmp: duplicated == 0
	je malloc_fail					; if true: goto malloc_fail
	jne copy						; if false: goto copy
	
	malloc_fail:
		mov rax, 0					; set return value = NULL
		jmp end
		
	copy:
		mov rdi, r14				; passing parameter: dst = duplicated
		mov rsi, r12				; passing parameter: src = s1
		call _ft_strcpy				; calling ft_strcpy
		mov r14, rax				; getting returned value (just is case)
		mov rax, r14				; set returned value = ft_strcpy's return value
		jmp end
	
	end:
		;

	pop r14
	pop r13
	pop r12
	
	ret								; do return
