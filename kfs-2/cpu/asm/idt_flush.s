[GLOBAL __asm_kfs_idt_flush]    ; Allows the C code to call idt_flush().

__asm_kfs_idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]        ; Load the IDT pointer.
   ret
