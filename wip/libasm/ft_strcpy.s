global _ft_strcpy
section .text

; Memory Map
; +----------+-------+--------------+---------+------+----+--------+
; |  origin  | local |     type     |  size   | from | to | offset |
; +----------+-------+--------------+---------+------+----+--------+
; | argument | dst   | char *       | 8 (ptr) |    0 |  8 |     24 |
; | argument | src   | const char * | 8 (ptr) |    8 | 16 |     16 |
; | variable | start | char *       | 8 (ptr) |   16 | 24 |      8 |
; +----------+-------+--------------+---------+------+----+--------+

_ft_strcpy:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)

	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (char *) dst
	mov		QWORD [rbp - 16], rsi		; Storing in [ 8 to 16 ] <- arg2: (const char *) src

	mov		rax, QWORD [rbp - 24]		; rax = [ 0 to 8 ] -> dst
	mov		QWORD [rbp - 8], rax		; Storing in [ 16 to 24 ] <- rax

	.loop:
		mov		rax, QWORD [rbp - 16]	; rax = [ 8 to 16 ] -> src
		movzx	eax, BYTE [rax]			; Casted content of rax as BYTE
		cmp		eax, 0					; Condition
		jne		.copy					; if (*src != 0): goto copy
		jmp		.endloop				; goto endloop

	.copy:
		mov		rax, QWORD [rbp - 16]	; rax = src
		movzx	edx, BYTE [rax]			; edx = *src
		mov		rax, QWORD [rbp - 24]	; rax = dst
		mov		BYTE [rax], dl			; *rax = dl --> *dst = *src
		
		add		QWORD [rbp - 24], 1		; Increment memory stored in [ 0 to 8 ] -> dst
		add		QWORD [rbp - 16], 1		; Increment memory stored in [ 8 to 16 ] -> src
		jmp		.loop					; goto: loop

	.endloop:
		mov	 rax, QWORD [rbp - 24]		; rax = [ 0 to 8 ] -> dst
		mov	 BYTE [rax], 0				; *rax = '\0'
		
	mov		rax, QWORD [rbp - 8]		; Setting returned value to [ 16 to 24 ]

	leave								; Releasing space
	ret									; Returning
