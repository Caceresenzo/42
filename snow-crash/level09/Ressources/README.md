# Level 09

## Initial Context

- Two file: `level09` and `token`

## Solving the Challenge

### Analyzing

```bash
$ ls -l
total 12
-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09 level09   26 Mar  5  2016 token
```

`level09` does not seems to behave like `cat`:

```bash
$ ./level09
You need to provied only one arg.
$ ./level09 token
tpmhr
$ cat token | hexdump -C
00000000  66 34 6b 6d 6d 36 70 7c  3d 82 7f 70 82 6e 83 82  |f4kmm6p|=..p.n..|
00000010  44 42 83 44 75 7b 7f 8c  89 0a                    |DB.Du{....|
0000001a
```

It looks like a custom encryption?

```bash
$ ltrace ./level09 token
...
ptrace(0, 0, 1, 0, 0xb7e2fe38) = -1
puts("You should not reverse this") = 28
...
```

We cannot use a debugger, this time we will have to do it by trial and error to understand what is being done.

```
$ ./level09 hello
hfnos
$ ./level09 abcdef
acegik
$ ./level09 aaaaaa
abcdef
$ ./level09 000000
012345
```

It seems to increment each character by its index?

### Exploiting

To decode this, we can subtract each character by its index.

Using a [simple script](./decode-simple.c) like ([full source code](./decode.c)):

```c
char input[] = { "hfnos" };
int length = strlen(input);

for (int index = 0; index < length; ++index)
  input[index] -= index;

write(1, input, length);
// hello
```

Running it:

```c
$ cd /tmp
$ nano -c level09.c # copy the content
$ gcc level09.c -o level09 -std=c99
$ ./level09 ~/token
....
```

Now we can log into `flag09` and do `getflag`.
