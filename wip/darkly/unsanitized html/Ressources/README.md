# Unsanitized Form Value

## Vulnerability

At the bottom of the site, there a `LEAVE A FEEDBACK` page: [`index.php?page=/?page=feedback`](http://darkly/index.php?page=feedback).

This page contains a simple form with a `name` and `message` inputs.

Simply submitting "`script`" in the `message` reveal the flag:
```
The flag is : ...
```

## Possible Fix

- Sanitize user inputs.
