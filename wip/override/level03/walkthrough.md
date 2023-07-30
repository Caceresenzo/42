# Level 03

## Initial Context

- One file: `level03`

## Solving the Challenge

The program expects a password.

By looking at the decompiled code, nothing is exploitable, but we need to find the right input to trigger a cypher.

It is comparable to a Cesar code but with XOR instead.

To find the right number, we can brute-force the first letter `Q` with all of the combination to find which value outputs `C`.

```python
>>> for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 17, 18, 19, 20, 21]:
...    letter = chr(ord("Q") ^ i)
...    print(i, letter, letter == "C")
...
1 P False
2 S False
3 R False
4 U False
5 T False
6 W False
7 V False
8 Y False
9 X False
16 A False
17 @ False
18 C True
19 B False
20 E False
21 D False
```

Its `18`.

Before the `decrypt` function is called, the input is substracted from `322424845` so:
```
18 = 322424845 - x
x = 322424845 - 18
x = 322424827
```

The password is `322424827`.

```bash
$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
<flag>
```
