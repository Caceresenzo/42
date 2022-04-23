# Level 13

## Initial Context

- A single file: `level13`

## Solving the Challenge

### Analyzing

```bash
$ ls -l
total 8
-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
```

Running the file tells us that a certain user need to do it:

```bash
$ ./level13
UID 2013 started us but we we expect 4242
```

Since we cannot create a user, we somehow need to bypass the check.

### Exploiting

Using [GDB](https://www.sourceware.org/gdb/), we can see the assembly of the file.

```bash
$ gdb ./level13
(gdb) disass main
Dump of assembler code for function main:
   0x0804858c <+0>:     push   %ebp
   0x0804858d <+1>:     mov    %esp,%ebp
   0x0804858f <+3>:     and    $0xfffffff0,%esp
   0x08048592 <+6>:     sub    $0x10,%esp
   # calling getuid()
   0x08048595 <+9>:     call   0x8048380 <getuid@plt>
   # comparing the return value with 4242 (0x1092)
   0x0804859a <+14>:    cmp    $0x1092,%eax
   # if equal, jump to main+63, else continue
   0x0804859f <+19>:    je     0x80485cb <main+63>
   # printing that getuid() didn't returned 4242
   0x080485a1 <+21>:    call   0x8048380 <getuid@plt>
   0x080485a6 <+26>:    mov    $0x80486c8,%edx
   0x080485ab <+31>:    movl   $0x1092,0x8(%esp)
   0x080485b3 <+39>:    mov    %eax,0x4(%esp)
   0x080485b7 <+43>:    mov    %edx,(%esp)
   0x080485ba <+46>:    call   0x8048360 <printf@plt>
   0x080485bf <+51>:    movl   $0x1,(%esp)
   # exiting
   0x080485c6 <+58>:    call   0x80483a0 <exit@plt>
   # calling a decoder?
   0x080485cb <+63>:    movl   $0x80486ef,(%esp)
   0x080485d2 <+70>:    call   0x8048474 <ft_des>
   0x080485d7 <+75>:    mov    $0x8048709,%edx
   0x080485dc <+80>:    mov    %eax,0x4(%esp)
   0x080485e0 <+84>:    mov    %edx,(%esp)
   0x080485e3 <+87>:    call   0x8048360 <printf@plt>
   0x080485e8 <+92>:    leave
   0x080485e9 <+93>:    ret
End of assembler dump.
(gdb)
```

So the code would look like:

```c
if (getuid() != 4242) {
  printf("error\n");
  exit(1);
}

printf("the flag is: ...\n");
```

We can add a breakpoint at the `cmp` and `run` the program:

```bash
(gdb) break *0x0804859a
Breakpoint 1 at 0x804859a
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 1, 0x0804859a in main ()
```

Once the breakpoint is reached, we can see that the `eax`'s value is 2013 (a.k.a `level13`'s user id).

```bash
(gdb) info register
eax            0x7dd    2013
...
```

Now we can set `eax` register to `4242`:

```bash
(gdb) set $eax=4242
(gdb) info register
eax            0x1092   4242
...
```

And continue:

```bash
(gdb) continue
Continuing.
your token is ....
```
