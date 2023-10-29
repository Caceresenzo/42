# Level 00

## Initial Context

- One file: `level00`

## Solving the Challenge

The file expects a password.

The code show that the password is got via a `scanf` and compared against the value `5276`.

```bash
$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
<flag>
```
