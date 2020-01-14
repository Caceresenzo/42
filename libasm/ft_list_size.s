global _ft_list_size
section .text

; Memory Map
; +----------+------------+----------+---------+------+----+--------+
; |  origin  |   local    |   type   |  size   | from | to | offset |
; +----------+------------+----------+---------+------+----+--------+
; | argument | begin_list | t_list * | 8 (ptr) |    0 |  8 |      8 |
; +----------+------------+----------+---------+------+----+--------+

_ft_list_size:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 16						; Reserving space (% 16)

	mov		QWORD [rbp - 8], rdi		; Storing in [ 0 to 8 ] <- arg1: (t_list *) begin_list

	mov		rax, QWORD [rbp - 8]		; rax = [ 0 to 8 ] = 'begin_list'

	cmp		rax, 0						; Condition
	je		.return						; if (begin_list->next == NULL): goto return

	mov		rax, QWORD [rax + 8]		; rax = [ rax + 8 ] --> begin_list->next

	mov		rdi, rax					; Setting argument 'begin_list' = rax = 'begin_list->next'
	call	_ft_list_size				; Calling ft_list_size
	add		DWORD eax, 1				; Incrementing returned value

	.return:
		;

	leave								; Releasing space
	ret									; Returning