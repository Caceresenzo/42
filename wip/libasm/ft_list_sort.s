global _ft_list_sort
section .text

; Memory Map
; +----------+------------+-----------+----------+------+----+--------+
; |  origin  |   local    |   type    |   size   | from | to | offset |
; +----------+------------+-----------+----------+------+----+--------+
; | argument | begin_list | t_list ** | 8 (ptr)  |    0 |  8 |     56 |
; | argument | cmp        | int (*)() | 8 (ptr)  |    8 | 16 |     48 |
; | variable | current    | t_list *  | 8 (ptr)  |   16 | 24 |     40 |
; | variable | end        | t_list *  | 8 (ptr)  |   24 | 32 |     32 |
; | variable | swapped    | bool      | 1 (byte) |   32 | 33 |     24 |
; | variable | swap_tmp   | void *    | 8 (ptr)  |   40 | 48 |     16 |
; +----------+------------+-----------+----------+------+----+--------+

_ft_list_sort:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 64						; Reserving space (% 16)

	mov		QWORD [rbp - 56], rdi		; Storing in [ 0 to 8 ] <- arg1: (t_list **) begin_list
	mov		QWORD [rbp - 48], rsi		; Storing in [ 8 to 16 ] <- arg1: (int (*)()) cmp

	mov		rax, QWORD [rbp - 56]		; rax = [ 0 to 8 ] = 'begin_list'
	mov		rax, QWORD [rax]			; rax = *rax = *'begin_list'
	
	cmp		rax, 0						; Condition
	je		.return						; if (*begin_list == NULL): goto return

	mov		QWORD [rbp - 32], 0	 		; Storing in [ 24 to 32 ] <- 'end' = NULL
	mov		BYTE [rbp - 24], 1	 		; Storing in [ 32 to 33 ] <- 'swapped' = true

	jmp		.loop_swapped				; goto: loop_swapped

	.loop_sort:		
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rax, QWORD [rax + 8]	; rax = [ rax + 8 ] --> current->next

		mov		rdx, QWORD [rbp - 32]	; rdx = [ 24 to 32 ] = 'end'

		cmp		rax, rdx				; Condition
		je		.endloop_sort			; if (current->next == end): goto endloop_sort
		
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rdi, QWORD [rax + 0]	; Setting parameter 'arg0' = [ rax + 0] = 'current'->data
		
		mov		rax, QWORD [rax + 8]	; rax = [ rax + 8 ] = 'current' = 'current->next'
		mov		rsi, QWORD [rax + 0]	; rsi = [ rax + 0 ] = 'current->next->data'
		
		mov		rax, QWORD [rbp - 48]	; rax = [ 8 to 16 ] = 'cmp'
		call	rax						; Calling (*cmp)
		
		cmp		eax, 0					; Condition // AS 32BIT SIGNED INTEGER	
		jg		.loop_sort_swap			; if (returned > 0): goto loop_sort_swap
		
		jmp		.loop_sort_after		; goto: loop_sort_after
		
	.loop_sort_swap:
		mov		BYTE [rbp - 24], 1	 	; Storing in [ 32 to 33 ] <- 'swapped' = true

		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rax, QWORD [rax + 0]	; rax = [ rax + 0 ] --> 'current'->data
	
		mov		QWORD [rbp - 16], rax	; Storing in [ 40 to 48 ] <- 'swap_tmp' = rax
		
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rax, QWORD [rax + 8]	; rax = [ rax + 8 ] --> 'current'->next
		mov		rdx, QWORD [rax + 0]	; rdx = [ rax + 0 ] --> 'current'->next->data
	
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		QWORD [rax + 0], rdx	; Storing in [ rax + 0 ] <- 'current'->next = 'current'->next->data
	
		mov		rdx, QWORD [rbp - 16]	; rdx = [ 40 to 48 ] = 'swap_tmp'
		
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rax, QWORD [rax + 8]	; rax = [ rax + 8 ] --> 'current'->next
		mov		QWORD [rax + 0], rdx	; Storing in [ rax + 0 ] <- 'current'->next->data = 'current'->next

		jmp		.loop_sort_after		; goto: loop_sort_after
	
	.loop_sort_after:
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		rax, QWORD [rax + 8]	; rax = [ rax + 8 ] = 'current'->next
		mov		QWORD [rbp - 40], rax	; Storing in [ 16 to 24 ] <- 'current' = 'current'->next

		jmp		.loop_sort				; goto: loop_sort
	
	.endloop_sort:
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'current'
		mov		QWORD [rbp - 32], rax	; Storing in [ 24 to 32 ] <- 'end' = 'current'

		jmp		.loop_swapped			; goto: loop_swapped

	.loop_swapped:
		mov		al, BYTE [rbp - 24]		; rax = [ 32 to 33 ] <- 'swapped' 
		
		cmp		al, 0					; Condition
		je		.endloop_swapped		; if (!swapped): goto endloop_swapped
		
		mov		BYTE [rbp - 24], 0	 	; Storing in [ 32 to 33 ] <- 'swapped' = false

		mov		rax, QWORD [rbp - 56]	; rax = [ 0 to 8 ] = 'begin_list'
		mov		rax, QWORD [rax]		; rax = *rax = *'begin_list'

		mov		QWORD [rbp - 40], rax	; Storing in [ 16 to 24 ] <- 'current' = *'begin_list
		
		jmp		.loop_sort				; goto: loop_sort
		
	.endloop_swapped:
		;

	.return:
		;

	leave								; Releasing space
	ret									; Returning