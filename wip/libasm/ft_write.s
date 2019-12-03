global _ft_write
section .text

; https://filippo.io/linux-syscall-table/ 
; https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master

; https://stackoverflow.com/a/48845698/7292958 (reason of the 0x2000000 offset)

_ft_write:
	mov r12, rdi					; // Argument 1: (int) fildes
	mov r13, rsi					; // Argument 2: (void *) buf
	mov r14, rdx					; // Argument 3: (size_t) nbyte

	mov rax, 0x2000004				; set to syscall #4: write

	mov rdi, r12					; passing parameter: file descriptor
	mov rsi, r13					; passing parameter: buffer
	mov rdx, r14					; passing parameter: length
	syscall							; do syscall

	ret								; do return
