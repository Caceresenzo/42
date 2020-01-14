global _ft_read
section .text

; Memory Map
; +----------+--------+--------+----------+------+----+--------+
; |  origin  | local  |  type  |   size   | from | to | offset |
; +----------+--------+--------+----------+------+----+--------+
; | argument | fildes | int    | 4 (int)  |    0 |  4 |     28 |
; | argument | buf    | void * | 8 (ptr)  |    4 | 12 |     20 |
; | argument | nbyte  | size_t | 8 (long) |   12 | 20 |     12 |
; +----------+--------+--------+----------+------+----+--------+

; https://filippo.io/linux-syscall-table/ 
; https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master

; https://stackoverflow.com/a/48845698/7292958 (reason of the 0x2000000 offset)

_ft_read:
	push	rbp							; Saving register: rbp

	mov		rbp, rsp					; Saving stack pointer: rsp
	sub		rsp, 32						; Reserving space (% 16)

	mov		DWORD [rbp - 28], edi		; Storing in [ 0 to 8 ] <- arg1: (int) fildes
	mov		QWORD [rbp - 20], rsi		; Storing in [ 8 to 16 ] <- arg2: (void *) buf
	mov		QWORD [rbp - 12], rdx		; Storing in [ 8 to 16 ] <- arg3: (size_t) nbyte

	mov		rax, 0x2000003				; Setting syscall ID to #3: 'read'

	mov edi, DWORD [rbp - 28]			; Passing parameter: 'file fildes'
	mov rsi, QWORD [rbp - 20]			; Passing parameter: 'buf'
	mov rdx, QWORD [rbp - 12]			; Passing parameter: 'nbyte'

	syscall								; Doing syscall

	leave								; Releasing space
	ret									; Returning
