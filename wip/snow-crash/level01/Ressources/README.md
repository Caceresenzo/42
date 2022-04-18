# Level 01

## Initial Context

- Empty home directory.
- We must find `flag01`'s password.

## Solving the Challenge

Where are passwords stored?
- in `/etc/passwd`
- in `/etc/shadow`

We don't have access to `/etc/shadow` but doing a `grep` on `/etc/passwd` can reveal us something:

```bash
$ cat /etc/passwd | grep flag01
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

### Cracking the password

Using [John the Ripper](https://linuxconfig.org/password-cracking-with-john-the-ripper-on-linux) we can try to crack the password.

The `incremental` mode will try every [character combination to resolve the password](http://manpages.ubuntu.com/manpages/bionic/man8/john.8.html#:~:text=character%20combination%20to%20resolve%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20the%20password).

First prepare the environment:

```bash
echo 'flag01:42hDRfypTqqnw' > /tmp/level01_passwd
```

Then run `john`:

```bash
$ john -incremental /tmp/level01_passwd
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 128/128 SSE2-16])
Warning: MaxLen = 13 is too large for the current hash type, reduced to 8
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (flag01)
1g 0:00:00:01 0.8064g/s 2465Kp/s 2465Kc/s 2465KC/s abcdels..abcdana
Use the "--show" option to display all of the cracked passwords reliably
Session completed
```

We have our flag: `abcdefg`