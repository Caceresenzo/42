global _ft_list_push_front
section .text

extern _malloc

; Memory Map
; +----------+------------+-----------+---------+------+----+--------+
; |  origin  |   local    |   type    |  size   | from | to | offset |
; +----------+------------+-----------+---------+------+----+--------+
; | argument | begin_list | t_list ** | 8 (ptr) |    0 |  8 |     24 |
; | argument | data       | void *    | 8 (ptr) |    8 | 16 |     16 |
; | variable | lst        | t_list *  | 8 (ptr) |   16 | 24 |      8 |
; +----------+------------+-----------+---------+------+----+--------+

_ft_list_push_front:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)

	mov		QWORD [rbp - 24], rdi		; Storing in [ 0 to 8 ] <- arg1: (t_list **) begin_list
	mov		QWORD [rbp - 16], rsi		; Storing in [ 8 to 16 ] <- arg2: (void *) data

	mov		rdi, 16						; Setting parameter 'size' = sizeof(t_list) = 16
	call	_malloc						; Calling malloc
	mov		QWORD [rbp - 8], rax		; Storing return in [ 16 to 24 ] <- 'lst' = rax

	cmp		rax, 0						; Condition
	je		.return						; if (returned == NULL): goto return
	
	mov		rax, QWORD [rbp - 8]		; rax = [ 16 to 24 ] = 'lst'
	mov		rdx, QWORD [rbp - 16]		; rdx = [ 8 to 16 ] = 'data'

	mov		QWORD [rax + 0], rdx		; lst->data = rdx
	mov		QWORD [rax + 8], 0			; lst->next = NULL

	mov		rdx, QWORD [rbp - 24]		; rdx = [ 0 to 8 ] = 'begin_list'
	mov		QWORD rdx, [rdx]			; rdx = *rdx = *'begin_list'
	mov		QWORD [rax + 8], rdx		; lst->next = rdx
	
	mov		rdx, QWORD [rbp - 24]		; rdx = [ 0 to 8 ] = 'begin_list'
	mov		QWORD [rdx], rax			; *rdx = rax --> *begin_list = lst

	.return:
		;
	
	leave								; Releasing space
	ret									; Returning