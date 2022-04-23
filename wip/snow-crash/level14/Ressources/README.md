# Level 14

## Initial Context

- Empty home directory.
- Absolutly nothing to hack, except `getflag`.

## Solving the Challenge

### Analyzing

After much investigation, there is nothing vulnerable file, binary or script to exploit. The last thing is `getflag`.

However, running it with [GDB](https://www.sourceware.org/gdb/) tell us:

```bash
$ gdb getflag
(gdb) run
Starting program: /bin/getflag
You should not reverse this
```

Let's try to override that.

### Exploiting

If we disassemble `main`, we can see a call to `ptrace`.

```bash
(gdb) disass main
Dump of assembler code for function main:
....
   0x08048989 <+67>:    call   0x8048540 <ptrace@plt>
   0x0804898e <+72>:    test   %eax,%eax
   0x08048990 <+74>:    jns    0x80489a8 <main+98>
...
```

So let's break after the call:

```bash
(gdb) break *0x804898e
Breakpoint 1 at 0x804898e
```

And run it:

```bash
(gdb) run
Starting program: /bin/getflag

Breakpoint 1, 0x0804898e in main ()
```

We are just after the call of `ptrace`. Since it returns -1, it will trigger the anti-debugger detection. To counter that, we can override the return value and set it to 0.

```bash
(gdb) set $eax=0
(gdb) info register
eax            0x0      0
...
```

Then we can continue.

```bash
(gdb) continue
Continuing.
Check flag.Here is your token :
Nope there is no token here for you sorry. Try again :)
```

The message appears since we are not logged as one of the `flagXX` account.

We are trying to appear as if we were connected as `flag14` or user id 3014.

```bash
$ grep flag14 /etc/passwd
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
```

And it does seem that `getflag` call `getuid()` to know this information:

```bash
(gdb) disass main
Dump of assembler code for function main:
...
   0x08048afd <+439>:   call   0x80484b0 <getuid@plt>
   0x08048b02 <+444>:   mov    %eax,0x18(%esp)
...
```

So let's break just after the `getuid()` call.

```bash
(gdb) break *0x08048b02
Breakpoint 2 at 0x8048b02
```

And let re-run everything.

```bash
(gdb) run
Starting program: /bin/getflag

Breakpoint 1, 0x0804898e in main ()
(gdb) # redoing the first part
(gdb) set $eax=0
(gdb) continue
Continuing.

Breakpoint 2, 0x08048b02 in main ()
```

Once we reached the second breakpoint, we need to set the return value to `flag14`'s user id.

```bash
(gdb) set $eax=3014
```

And then we can continue.

```bash
(gdb) continue
Continuing.
Check flag.Here is your token : ... 
```

Success!

Since its supposed to be `level15`'s password and there is no `level15`, should it be considered as the flag?

Logging as `flag14` with this as the password:

```bash
$ su flag14
Password:
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)
flag14@SnowCrash:~$ getflag
Check flag.Here is your token : ....
```

Yes, it was the flag.