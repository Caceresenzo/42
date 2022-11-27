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

## Why it is dangerous

Even if some information it not directly shown to the user, it is still sent to the server.
If the server does not validate the inputs, important information could be modified to change the behaviour of a page.

The commons use cases for these hidden fields are:
- captcha codes
- [CRSF tokens](https://portswigger.net/web-security/csrf/tokens)

Using it for things likes pre-filled inputs could cause problems because [they could be modified](https://docs.fluidattacks.com/criteria/vulnerabilities/093/).

## Possible Fix

- Add a field for the username and send the password to the correct email only if it matches the requested username
