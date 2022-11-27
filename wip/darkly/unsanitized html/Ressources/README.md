# Unsanitized HTML

## Vulnerability

At the bottom of the site, there a `LEAVE A FEEDBACK` page: [`index.php?page=/?page=feedback`](http://darkly/index.php?page=feedback).

This page contains a simple form with a `name` and `message` inputs.

Simply submitting "`script`" in the `message` reveal the flag:
```
The flag is : ...
```

It seems that this challenge is broken. The vulnerability should be that we could inject code in the displayed messages such as:

```html
<script>alert(document.cookie)</script>
```

## Why it is dangerous

Sending `javascript` code that is served by a server is called an XSS attack.

It enables one to execute arbitrary code on somebody else's browser.

**Example 1:** @derGeruhn wrote a  to self-retweeting tweet: 
```html
<script class="xss">$('.xss').parents().eq(1).find('a').eq(1).click();$('[data-action=retweet]').click();alert('XSS in Tweetdeck')</script>♥
```

**Example 2:** Samy Kamkar, using the same principle, created [a worm](https://en.wikipedia.org/wiki/Samy_(computer_worm)) that propagated over the social networking site MySpace.

## Possible Fix

- Sanitize user inputs server-side.
