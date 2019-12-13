global _ft_strdup
section .text

extern _malloc
extern _ft_strlen
extern _ft_strcpy

; Memory Map
; +----------+------------+--------------+----------+------+----+--------+
; |  origin  |   local    |     type     |   size   | from | to | offset |
; +----------+------------+--------------+----------+------+----+--------+
; | argument | s1         | const char * | 8 (ptr)  |    0 |  8 |     24 |
; | variable | length     | size_t       | 8 (long) |    8 | 16 |     16 |
; | variable | duplicated | char *       | 8 (ptr)  |   16 | 24 |      8 |
; +----------+------------+--------------+----------+------+----+--------+

_ft_strdup:
	push	rbp							; Saving register: rbp
	
	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)
	
	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (const char *) s1

	mov		rax, QWORD [rbp - 24]		; rax = [ 0 to 8 ] -> s1
	mov		rdi, rax					; Setting argument 's' = rax
	call	_ft_strlen					; Calling ft_strlen
	mov		QWORD [rbp - 16], rax		; Storing in [ 8 to 16 ] <- return: (size_t)

	mov		rax, QWORD [rbp - 16]		; rax = [ 8 to 16 ] -> length
	mov		rdi, rax					; Setting argument 'size' = length
	call	_malloc						; Calling malloc
	mov		QWORD [rbp - 8], rax		; Storing in [ 12 to 20 ] <- return: (size_t)

	mov		rax, QWORD [rbp - 8]		; rax = [ 16 to 24 ] -> duplicated
	mov		rdi, rax					; Setting argument 'dest' = rax
	mov		rax, QWORD [rbp - 24]		; rax = [ 0 to 8 ] -> s1
	mov		rsi, rax					; Setting argument 'src' = rax
	call	_ft_strcpy					; Calling ft_strcpy

	mov		rax, QWORD [rbp - 8]		; Setting returned value to [ 16 to 24 ]

	leave								; Releasing space
	ret									; Returning
