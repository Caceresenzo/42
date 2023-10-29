# Level 06

## Initial Context

- One file: `level06`

## Solving the Challenge

The program expects a login and a serial number.

The login is hashed and compared against the serial number, if they match, we get a shell.

Even though the code has protection against tools like `gdb`, we can break before those checks and continue.

To get the correct serial number, we have to run the program within `gdb` and break before the final check to extract the value.
Its easier than re-implementing the hashing algorithm.

We first need to break right after a `ptrace` call at `auth+114`:

```bash
0x80487b5 <auth+109>    call   0x80485f0 <ptrace@plt>
0x80487ba <auth+114>    cmp    eax,0xffffffff
```

And then break at the final check at `auth+286`:

```bash
0x8048866 <auth+286>    cmp    eax,DWORD PTR [ebp-0x10]
```

By running the program with a dummy serial, we can extract the real one.

```bash
$ gdb ./level06 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
...
(gdb) set disassembly-flavor intel
(gdb) break *auth+114
Breakpoint 1 at 0x80487ba
(gdb) break *auth+286
Breakpoint 2 at 0x8048866
(gdb) run
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: helloworld
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42

Breakpoint 1, 0x080487ba in auth ()
(gdb) # set ptrace's response to 0
(gdb) set $eax = 0
(gdb) continue
Continuing.

Breakpoint 2, 0x08048866 in auth ()
(gdb) # show the serial for login "helloworld"
(gdb) x/d $ebp-0x10
0xffffd6a8:     6236969
```

Now that we have the combo `helloworld:6236969`, we can get a shell.

```bash
$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: helloworld
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6236969
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
<flag>
```
