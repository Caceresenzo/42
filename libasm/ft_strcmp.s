global _ft_strcmp
section .text

; Memory Map
; +----------+-------+--------+---------+------+----+--------+
; |  origin  | local |  type  |  size   | from | to | offset |
; +----------+-------+--------+---------+------+----+--------+
; | argument | s1    | char * | 8 (ptr) |    0 |  8 |     24 |
; | argument | s2    | char * | 8 (ptr) |    8 | 16 |     16 |
; | variable | diff  | int    | 4 (int) |   16 | 24 |      8 |
; +----------+-------+--------+---------+------+----+--------+

_ft_strcmp:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)

	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (char *) s1
	mov		QWORD [rbp - 16], rsi		; Storing in [ 8 to 16 ] <- arg2: (char *) s2

	mov		QWORD [rbp - 8], 0			; Storing in [ 16 to 24 ] <- 'diff' = 0

	.loop:
		mov		rax, QWORD [rbp - 24]	; rax = [ 0 to 8 ] -> s1
		movzx	eax, BYTE [rax]			; Casted content of rax as BYTE
		mov		rdx, QWORD [rbp - 16]	; rdx = [ 8 to 16 ] -> s2
		movzx	edx, BYTE [rdx]			; Casted content of rdx as BYTE

		cmp		eax, 0					; Condition
		jne		.check_diff				; if (*s1 != 0): goto check_diff
		jmp		.endloop				; goto endloop

	.check_diff:
		cmp		eax, edx				; Condition
		jne		.endloop				; if (*s1 != *s2): goto endloop
		jmp		.increment				; goto increment

	.increment:
		add		QWORD [rbp - 24], 1		; Increment memory stored in [ 0 to 8 ] -> s1
		add		QWORD [rbp - 16], 1		; Increment memory stored in [ 8 to 16 ] -> s2
		jmp		.loop					; goto: loop

	.endloop:
		mov		QWORD [rbp - 8], rax	; Storing in [ 16 to 24 ] value *s1
		sub		QWORD [rbp - 8], rdx	; Substracting from [ 16 to 24 ] valur *2 --> *s1 - *s2
		
	mov		rax, QWORD [rbp - 8]		; Setting returned value to [ 16 to 24 ]

	leave								; Releasing space
	ret									; Returning