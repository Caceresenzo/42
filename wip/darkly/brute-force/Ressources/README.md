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

- Use a more complex password.
- Use a multiple-factor system.
