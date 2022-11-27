# Login Brute-force

## Vulnerability

The site includes a `signin` page at [`index.php?page=signin`](http://darkly/?page=signin).

A good choice would be to try to force account like `admin`, `root`, `master`, or `owner`.

Using a [1 million most common password list](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/10-million-password-list-top-10000.txt), we can brute-force the login URL.

Using the small [`main.py`](./main.py) script, it only takes less than a minute since the password was in the first few lines of the list.
```bash
$ python3 main.py
password list is missing, downloading...
password: shadow       
17it [00:34,  2.00s/it]
```

Trying to login with the user `admin` and password `shadow` gave us the flag: [[run]](http://darkly/?page=signin&username=admin&password=shadow&Login=Login#)
```
The flag is : ... 
```

## Possible Fix

- Use a more complex password. Specifically:
  * check that it is not on a leaked password list such as [rockyou.txt](https://www.kaggle.com/datasets/wjburns/common-password-list-rockyoutxthuu). One can use [;--have i been pwned?](https://haveibeenpwned.com/Passwords) by security expert Troy Hunt.
  * check that your password strength is high with tools such as [`zxcvbn`](https://dropbox.tech/security/zxcvbn-realistic-password-strength-estimation).
  * use password rules such as in [born2beroot](https://cdn.intra.42.fr/pdf/pdf/57308/en.subject.pdf).
  Make them more complex though because a password such as `Abandon1ng` is deemed 'very weak' by [`zxcvbn`](https://dropbox.tech/security/zxcvbn-realistic-password-strength-estimation).
  To be safe, make it random and at least [14-character long](https://images.ctfassets.net/7rncvj1f8mw7/6dWQBFgA3yRnkhF3QoK0Bt/3b48cc7fad6eb90f86c8de5d092bbc22/pw-strength-test-chart.png?w=1117&h=1200).
- Use a multiple-factor system.
