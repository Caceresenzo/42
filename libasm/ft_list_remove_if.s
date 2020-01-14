global _ft_list_remove_if
section .text

extern _free

; Memory Map
; +----------+------------+------------------+---------+------+----+--------+
; |  origin  |   local    |       type       |  size   | from | to | offset |
; +----------+------------+------------------+---------+------+----+--------+
; | argument | begin_list | t_list **        | 8 (ptr) |    0 |  8 |     56 |
; | argument | data_ref   | void *           | 8 (ptr) |    8 | 16 |     48 |
; | argument | cmp        | int (*)()        | 8 (ptr) |   16 | 24 |     40 |
; | argument | free_fct   | void (*)(void *) | 8 (ptr) |   24 | 32 |     32 |
; | variable | removed    | t_list *         | 8 (ptr) |   32 | 40 |     24 |
; | variable | next       | t_list **        | 8 (ptr) |   40 | 48 |     16 |
; +----------+------------+------------------+---------+------+----+--------+

_ft_list_remove_if:
	push	rbp							; Saving register: rbp
	
	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 64						; Reserving space (% 16)
	
	mov		QWORD [rbp - 56], rdi		; Storing in [ 0 to 8 ] <- arg1: (t_list **) begin_list
	mov		QWORD [rbp - 48], rsi		; Storing in [ 8 to 16 ] <- arg2: (void *) data_ref
	mov		QWORD [rbp - 40], rdx		; Storing in [ 16 to 24 ] <- arg3: (int (*)()) cmp
	mov		QWORD [rbp - 32], rcx		; Storing in [ 24 to 32 ] <- arg4: (void (*)(void *)) free_fct

	mov		QWORD [rbp - 24], 0			; Storing in [ 32 to 40 ] <- 'removed' = NULL
	mov		QWORD [rbp - 16], 0			; Storing in [ 40 to 48 ] <- 'next' = NULL		

	mov		rax, QWORD [rbp - 56]		; rax = [ 0 to 8 ] = 'begin_list'
	cmp		rax, 0						; Condition
	je		.return						; if (begin_list == NULL): goto return
	
	mov		rax, QWORD [rax]			; rax = *'begin_list'
	cmp		rax, 0						; Condition
	je		.return						; if (*begin_list == NULL): goto return

	mov		rax, QWORD [rax + 0]		; rax = *'begin_list'->data
	mov		rdi, rax					; Passing parameter: 'arg1'
	
	mov		rax, QWORD [rbp - 48]		; rax = [ 8 to 16 ] = 'data_ref'
	mov		rsi, rax					; Passing parameter: 'arg2'
	
	mov		rax, QWORD [rbp - 40]		; rax = [ 16 to 24 ] = 'cmp'
	
	call	rax							; Calling rax --> 'cmp'
	
	cmp		eax, 0						; Condition
	je		.remove						; if ((int) returned == 0): goto remove

	mov		rax, QWORD [rbp - 56]		; rax = [ 0 to 8 ] = 'begin_list'
	mov		rax, QWORD [rax]			; rax = *'begin_list'
	lea		rax, [rax + 8]				; rax = &(*'begin_list'->next)
	mov		QWORD [rbp - 16], rax		; Storing in [ 40 to 48 ] <- 'next' = rax

	jmp		.next						; else: goto next
	
	.remove:
		mov		rax, QWORD [rbp - 56]	; rax = [ 0 to 8 ] = 'begin_list'
		mov		rax, QWORD [rax]		; rax = *'begin_list'

		mov		QWORD [rbp - 24], rax	; Storing in [ 32 to 40 ] <- 'removed' = *'begin_list'

		mov		rax, QWORD [rbp - 56]	; rax = [ 0 to 8 ] = 'begin_list'
		mov		rdx, rax				; rdx = rax
		
		mov		rax, QWORD [rbp - 24]	; rax = [ 32 to 40 ] = 'removed'
		mov		rax, QWORD [rax + 8]	; rax = 'removed'->next

		mov		QWORD [rdx], rax		; Storing in [rdx] <- *'begin_list' = 'removed'->next
		
		mov		rax, QWORD [rbp - 24]	; rax = [ 32 to 40 ] = 'removed'
		mov		rax, QWORD [rax + 0]	; rax = 'removed'->data
		mov		rdi, rax				; Passing parameter: 'arg1'

		mov		rax, QWORD [rbp - 32]	; rax = [ 24 to 32 ] = 'free_fct'

		call	rax						; Calling rax --> 'free_fct'

		mov		rax, QWORD [rbp - 24]	; rax = [ 32 to 40 ] = 'removed'
		mov		rdi, rax				; Passing parameter: 'ptr'

		call	_free					; Calling free

		mov		rax, QWORD [rbp - 56]	; rax = [ 0 to 8 ] = 'begin_list'
		mov		QWORD [rbp - 16], rax	; Storing in [ 40 to 48 ] <- 'next' = rax

	.next:
		mov		rax, QWORD [rbp - 16]	; rax = [ 40 to 48 ] = 'next'
		mov		rdi, rax				; Passing parameter: 'begin_list'
		
		mov		rax, QWORD [rbp - 48]	; rax = [ 8 to 16 ] = 'data_ref'
		mov		rsi, rax				; Passing parameter: 'data_ref'
		
		mov		rax, QWORD [rbp - 40]	; rax = [ 16 to 24 ] = 'cmp'
		mov		rdx, rax				; Passing parameter: 'cmp'
		
		mov		rax, QWORD [rbp - 32]	; rax = [ 24 to 32 ] = 'free_fct'
		mov		rcx, rax				; Passing parameter: 'free_fct'

		call	_ft_list_remove_if		; Calling ft_list_remove_if
	
	.return:
		mov		rax, 0					; rax = 0

	leave								; Releasing space
	ret									; Returning
