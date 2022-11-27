# Domain Spoofing

## Vulnerability

At the very bottom of the page, there is a clickable `© BornToSec` link redirecting to: [`index.php?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f`](http://darkly/index.php?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f).

Looking at the page code, we can see a few comment like:
```html
<!--
You must come from : "https://www.nsa.gov/".
-->

<!--
[...]    Let's use this browser : "ft_bornToSec". It will help you a lot.
-->
```

`You must come from` means spoofing the [HTTP Referer Header](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Referer).
And `Let's use this browser` means spoofing the [HTTP User Agent Header](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/User-Agent).

So by doing the cURL command:
```bash
curl \
    -H 'Referer: https://www.nsa.gov/' \
    -H 'User-Agent: ft_bornToSec' \
    'http://darkly/index.php?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f'
```

We can see the flag:
```html
...
<h2> The flag is : ...</h2>
...
```

## Possible Fix

- Do not include the comments?
