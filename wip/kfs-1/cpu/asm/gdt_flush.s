[GLOBAL __asm_kfs_gdt_flush]    ; Allows the C code to call gdt_flush().

__asm_kfs_gdt_flush:
   mov eax, [esp+4]    ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]          ; Load the new GDT pointer

.reload_segments:
   jmp 0x08:.reload_cs ; 0x08 is the offset to our code segment: Far jump!

.reload_cs:
   mov eax, 0x10       ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax          ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   ret
