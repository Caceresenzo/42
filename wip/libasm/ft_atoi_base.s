global _ft_atoi_base
global _ft_atoi_base_is_whitespace
global _ft_atoi_base_resolve
section .text

extern _ft_strlen

; Memory Map: _ft_atoi_base
; +----------+----------+--------------+----------+------+----+--------+
; |  origin  |  local   |     type     |   size   | from | to | offset |
; +----------+----------+--------------+----------+------+----+--------+
; | argument | str      | const char * | 8 (ptr)  |    0 |  8 |     40 |
; | argument | base     | const char * | 8 (ptr)  |    8 | 16 |     32 |
; | variable | radix    | size_t       | 8 (long) |   16 | 24 |     24 |
; | variable | negative | int          | 4 (int)  |   24 | 32 |     16 |
; | variable | result   | long         | 8 (long) |   32 | 40 |      8 |
; +----------+----------+--------------+----------+------+----+--------+

; Memory Map: _ft_atoi_base_is_whitespace
; +----------+-------+--------------+----------+------+----+--------+
; |  origin  | local |     type     |   size   | from | to | offset |
; +----------+-------+--------------+----------+------+----+--------+
; | argument | c     | char         | 1 (byte) |    0 |  1 |      8 |
; +----------+-------+--------------+----------+------+----+--------+

; Memory Map: _ft_atoi_base_resolve
; +----------+-------+--------------+----------+------+----+--------+
; |  origin  | local |     type     |   size   | from | to | offset |
; +----------+-------+--------------+----------+------+----+--------+
; | argument | base  | const char * | 8 (ptr)  |    0 |  8 |     24 |
; | argument | c     | const char   | 1 (byte) |    8 | 16 |     16 |
; | variable | index | long         | 8 (long) |   16 | 24 |      8 |
; +----------+-------+--------------+----------+------+----+--------+

_ft_atoi_base:
	push	rbp							; Saving register: rbp
	
	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 64						; Reserving space (% 16)
	
	mov		QWORD [rbp - 40], rdi		; Storing in [ 0 to 8 ] <- arg1: (const char *) str
	mov		QWORD [rbp - 32], rsi		; Storing in [ 8 to 16 ] <- arg2: (const char *) base

	mov		QWORD [rbp - 16], 1			; Storing in [ 24 to 32 ] <- 'negative' = 1
	mov		QWORD [rbp - 8], 0			; Storing in [ 32 to 40 ] <- 'result' = 0

	mov		rax, QWORD [rbp - 32]		; rax = [ 8 to 16 ] -> 'base'
	mov		rdi, rax					; Setting argument 's' = rax
	call	_ft_strlen					; Calling ft_strlen
	mov		QWORD [rbp - 24], rax		; Storing in [ 16 to 20 ] <- 'radix' = return: (size_t)

	.loop_whitespace
		mov		rdi, QWORD [rbp - 40]	; rdi = [ 0 to 8 ] -> str
		movzx	edi, BYTE [rdi]			; Casted content of rdi as BYTE
		call	_ft_atoi_base_is_whitespace; Calling _ft_atoi_base_is_whitespace
		
		cmp		eax, 0					; Condition
		je		.endloop_whitespace		; if (returned == 0): goto endloop_whitespace
		
		add		QWORD [rbp - 40], 1		; Increment memory stored in [ 0 to 8 ] -> 'str'
		jmp		.loop_whitespace
	
	.endloop_whitespace
		;

	mov		rax, QWORD [rbp - 40]		; rax = [ 0 to 8 ] -> str
	movzx	eax, BYTE [rax]				; Casted content of rdi as BYTE

	cmp		BYTE eax, 43				; Condition
	je		.increment					; if (*str == '+'): goto increment
	cmp		BYTE eax, 45				; Condition
	je		.negate						; if (*str == '-'): goto negate
	
	jmp		.endsign					; else: goto endsign
	
	.negate:
		mov		QWORD [rbp - 16], -1	; Storing in [ 24 to 32 ] <- 'negative' = -1
	
	.increment:
		add		QWORD [rbp - 40], 1		; Increment memory stored in [ 0 to 8 ] -> 'str'
	
	.endsign:
		;

	mov		rdx, 0						; /!\ Important but don't know why...

	.loop:
		mov		rdi, QWORD [rbp - 32]	; Setting argument 'base' = 'base'
		mov		rsi, QWORD [rbp - 40]	; Setting argument 'c' = *str
		movzx	esi, BYTE [rsi]			; Casted as BYTE

		call	_ft_atoi_base_resolve	; Calling _ft_atoi_base_resolve
		cmp		rax, -1					; Condition
		je		.endloop				; if (returned == -1): goto endloop
		
		mov		rdx, QWORD [rbp - 32]	; rdx = [ 8 to 16 ] -> 'base'
		add		rdx, rax				; rdx += returned --> base[returned]
		movzx	edx, BYTE [rdx]			; Casted rax context as BYTE
		sub		rdx, 48					; rax -= '0'

		mov		rax, QWORD [rbp - 8]	; rdx = [ 32 to 40 ] -> 'result'
		imul	rax, QWORD [rbp - 24]	; rdx *= [ 16 to 20 ] --> rdx *= radix

		add		rax, rdx				; rdx += rax
		
		mov		QWORD [rbp - 8], rax	; Storing in [ 32 to 40 ] <- rdx
		add		QWORD [rbp - 40], 1		; Increment memory stored in [ 0 to 8 ] -> 'str'

		jmp .loop						; goto: loop

	.endloop:
		;

	mov		eax, DWORD [rbp - 8]		; Setting returned value to [ 40 to 48 ]
	imul	rax, QWORD [rbp - 16]		; returned value *= 'negate'

	leave								; Releasing space
	ret									; Returning


_ft_atoi_base_is_whitespace:
	push	rbp							; Saving register: rbp
	
	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 16						; Reserving space (% 16)

	mov		eax, edi
	mov		BYTE [rbp - 8], al			; Storing in [ 0 to 1 ] <- arg1: (const char) c
	
	cmp		BYTE [rbp - 8], 32			; Comparing for ' '
	je		.true

	cmp		BYTE [rbp - 8], 9			; Comparing for '\t'
	je		.true

	cmp		BYTE [rbp - 8], 10			; Comparing for '\n'
	je		.true

	cmp		BYTE [rbp - 8], 11			; Comparing for '\v'
	je		.true

	cmp		BYTE [rbp - 8], 12			; Comparing for '\f'
	je		.true

	cmp		BYTE [rbp - 8], 13			; Comparing for '\r'
	je		.true

	jmp		.false

	.true:
		mov		rax, 1					; Setting returned value to 1 ('true')
		jmp		.end					; goto: end
	
	.false:
		mov		rax, 0					; Setting returned value to 1 ('end')
		jmp		.end					; goto: end
	
	.end
		;

	leave								; Releasing space
	ret									; Returning
	

_ft_atoi_base_resolve:
	push	rbp							; Saving register: rbp
	
	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)
	
	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (const char *) str
	mov		BYTE [rbp - 16], sil		; Storing in [ 8 to 9 ] <- arg2: (const char) c

	mov		QWORD [rbp - 8], 0			; Storing in [ 12 to 20 ] <- 'index' = -1

	.loop:
		mov		rax, QWORD [rbp - 24]	; rax = [ 0 to 8 ] -> 'base'
		movzx	eax, BYTE [rax]			; Casted content of rax as BYTE

		cmp		eax, 0					; Condition
		je		.endloop_eol			; if (*base == 0): goto endloop_eol

		mov		dl, BYTE [rbp - 16]		; rdx = [ 8 to 9 ] -> 'c'

		cmp		rax, rdx				; Condition
		je		.endloop				; if (*base == c): goto endloop

		add		QWORD [rbp - 8], 1		; Increment memory stored in [ 12 to 20 ] -> 'index'
		add		QWORD [rbp - 24], 1		; Increment memory stored in [ 0 to 8 ] -> 'base'

		jmp		.loop					; goto: loop

	.endloop_eol:
		mov		QWORD [rbp - 8], -1		; Storing in [ 12 to 20 ] <- 'index' = -1

	.endloop:
		;

	mov		rax, QWORD [rbp - 8]		; Setting returned value to [ 12 to 20 ]

	leave								; Releasing space
	ret									; Returning