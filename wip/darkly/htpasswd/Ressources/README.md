# htpasswd

## Vulnerability

The [`robots.txt`](http://darkly/robots.txt) usually used by indexer contains the information to not look in the [`whatever`](http://darkly/whatever/) directory.

This directory only contains a `htpasswd` file.

This file contains a single line:
```
root:437394baff5aa33daa618be47b75cb49
```

Using a universal hash decryptor likes [hashes.com](https://hashes.com/en/decrypt/hash), the MD5 match has been found:
```
437394baff5aa33daa618be47b75cb49:qwerty123@:MD5
```

Theses inputs can be entered on: [`/admin/`](http://darkly/admin/).
Giving us the flag:
```
The flag is : ...
```

## Possible Fix

- Disable the listing.
- Disable the serving of this file.
