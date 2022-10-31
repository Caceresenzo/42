# Hidden Form Field

## Vulnerability

The `signin` page have a `I forgot my password` link to: [`index.php?page=recover`](http://darkly/index.php?page=recover).

The page contains a hidden input:
```html
<input type="hidden" name="mail" value="webmaster@borntosec.com" maxlength="15">
```

Trying the `Submit` button give a `Sorry Wrong Answer`.

Editing the `mail` value to anything else and retrying to `Submit` give the flag:
```
The flag is : ...
```

## Possible Fix

- Send the password via mail?
