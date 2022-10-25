# Unsanitized Form Value

## Vulnerability

At the top right of the site, there a `Survey` page: `http://darkly/index.php?page=survey`.

This page contains a Table with editable value.
When a value is edited, a request is made and the page is refreshed.

By sending a custom request with an invalid value:
```bash
curl \
  -H 'Content-Type: application/x-www-form-urlencoded' \
  --data-raw 'sujet=3&valeur=500000' \
  'http://darkly/index.php?page=survey'
```

We get the flag:
```html
<h2> The flag is ...</h2>
```

## Possible Fix

- Do not include the comments?