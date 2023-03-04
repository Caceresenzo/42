# Level 00

## Initial Context

- One file: `level0`

## Solving the Challenge

Running the file without any argument yields a segmentation fault.
By using some arguments, it yields a simple `No !`

```bash
$ ./level0
Segmentation fault (core dumped)
$ ./level0 a
No !
$ ./level0 a b
No !
```

Since there is a segmentation fault, we can try to debug it using GDB.

```bash
$ gdb ./level0
(gdb) run
Program received signal SIGSEGV, Segmentation fault.
0x08049aff in ____strtol_l_internal ()
(gdb) bt
#0  0x08049aff in ____strtol_l_internal ()
#1  0x08049aaa in strtol ()
#2  0x0804972f in atoi ()
#3  0x08048ed9 in main ()
```

We can see that it failed when trying to do an `atoi`. Make sens since without arguments, the input string would be `NULL`.

To try to understand what the program does, we can break at the main function and print the assembly code.

```bash
$ gdb ./level0
(gdb) break main
Breakpoint 1 at 0x8048ec3
(gdb) run
Breakpoint 1, 0x08048ec3 in main ()
(gdb) layout asm
...
0x8048ed4 <main+20>     call   0x8049710 <atoi>
0x8048ed9 <main+25>     cmp    $0x1a7,%eax
0x8048ede <main+30>     jne    0x8048f58 <main+152>
...
```

We can easily see the `call` to `atoi`, followed by a `comparison` with `0x1a7` and a `jump if no equal`.

`0x1a7` in base `10` is `423`.

```bash
$ ./level0 423
$ whoami
level1
$ cat /home/user/level1/.pass
<flag>
```
