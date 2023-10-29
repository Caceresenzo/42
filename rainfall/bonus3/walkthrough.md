# Bonus 3

## Initial Context

- One file: `bonus3`

## Solving the Challenge

The program will give us a shell if we find the correct `end`'s password.

However, `argv[1]` is also used to set the null terminator in the password's buffer.

If we set it to `0`, the password buffer's length is technically zero, but the `strcmp("", "0")` will fails.

But `atoi` will returns `0` if the string is empty.
The password buffer's length will be zero, and the `strcmp` will be against another empty buffer.

```bash
$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
<flag>
```

## The End

```bash
$ su end
Password:
end@RainFall:~$ ls
end
end@RainFall:~$ cat end
Congratulations graduate!
```