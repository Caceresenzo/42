# Bad Form Validation

## Vulnerability

At the top right of the site, there a `Survey` page: [`index.php?page=survey`](http://darkly/index.php?page=survey).

This page contains a table with editable values.
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
...
<h2> The flag is ...</h2>
...
```

## Possible Fix

- Do a server-side validation on inputs.
