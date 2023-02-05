[GLOBAL __asm_kfs_pit_disable]    ; Allows the C code to call pit_disable().

__asm_kfs_pit_disable:
   mov al, 0xff
   out 0xa1, al
   out 0x21, al
