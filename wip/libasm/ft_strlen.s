global _ft_strlen
section .text

; Memory Map
; +----------+--------+--------+----------+------+----+--------+
; |  origin  | local  |  type  |   size   | from | to | offset |
; +----------+--------+--------+----------+------+----+--------+
; | argument | s      | char * | 8 (ptr)  |    0 |  8 |     24 |
; | variable | length | size_t | 8 (long) |    8 | 16 |     16 |
; +----------+--------+--------+----------+------+----+--------+

_ft_strlen:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)
	
	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (const char *) s
	mov		QWORD [rbp - 16], 0			; Storing in [ 8 to 16 ] <- 'length' = 0

	.loop:
		mov		rax, QWORD [rbp - 24]	; rax = [ 0 to 8 ] -> s
		movzx	eax, BYTE [rax]			; Casted content of rax as BYTE
		cmp		eax, 0					; Condition
		jne		.increment				; if (*s != 0): goto increment
		jmp		.endloop				; goto endloop

	.increment:
		add		QWORD [rbp - 24], 1		; Increment memory stored in [ 0 to 8 ] -> s
		add		QWORD [rbp - 16], 1		; Increment memory stored in [ 8 to 16 ] -> 'length'
		jmp		.loop					; goto: loop

	.endloop:
		;
	
	mov		rax, QWORD [rbp - 16]		; Setting returned value to [ 8 to 16 ] -> 'length'

	leave								; Releasing space
	ret									; Returning