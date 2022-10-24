# Unprotected Redirection Parameter

## Vulnerability

At the bottom of the page, there is a few buttons redirecting to some social network pages.
The URL is as follow: `http://darkly/index.php?page=redirect&site={site}`

We can get the flag by using a value which is not in the following list:
- `facebook`
- `twitter`
- `instagram`

The URL `http://darkly/index.php?page=redirect&site=test` gave us the flag:
```
Good Job Here is the flag : ...
```

## Possible Fix

- Sanitize the user input and only accept a limited amount of value.
