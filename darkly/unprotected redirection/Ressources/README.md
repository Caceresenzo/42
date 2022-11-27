# Unprotected Redirection Parameter

## Vulnerability

At the bottom of the page, there is a few buttons redirecting to some social network pages.
The URL is as follow: `index.php?page=redirect&site={site}`.

We can get the flag by using a value which is not in the following list:
- [`facebook`](http://darkly/index.php?page=redirect&site=facebook)
- [`twitter`](http://darkly/index.php?page=redirect&site=twitter)
- [`instagram`](http://darkly/index.php?page=redirect&site=instagram)

A simple value link `site=test` gave us the flag: [[run]](http://darkly/index.php?page=redirect&site=test)
```
Good Job Here is the flag : ...
```

## Possible Fix

- Sanitize the user input and only accept a limited amount of value.
