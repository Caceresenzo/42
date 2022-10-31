# The `.hidden` Directory

## Vulnerability

The `robots.txt` usually used by indexer contains the information to not look in the [`.hidden`](http://darkly/.hidden/) directory.

The listing shows a lot of directories with random names.
After a depth of 3, a README file contains one of 5 text:
- Tu veux de l'aide ? Moi aussi !
- Demande à ton voisin de gauche
- Demande à ton voisin du dessus
- Non ce n'est toujours pas bon ...
- Toujours pas tu vas craquer non ?

By downloading recursively all of the directories using `wget`, we can search for the flag.

```bash
$ mkdir -p storage
$ cd storage
$ wget -e robots=off -r -np http://darkly/.hidden/
```

Once everything is downloaded, a simple grep is enough to find the flag: [[run]](http://darkly/.hidden/whtccjokayshttvxycsvykxcfm/igeemtxnvexvxezqwntmzjltkt/lmpanswobhwcozdqixbowvbrhw/README)
```bash
$ grep -Rn flag
darkly/.hidden/whtccjokayshttvxycsvykxcfm/igeemtxnvexvxezqwntmzjltkt/lmpanswobhwcozdqixbowvbrhw/README:1:Hey, here is your flag : ...
```

## Possible Fix

- Disable the listing.
- Require authentication.

## Reference

- [`wget` command](https://gist.github.com/simonw/27e810771137408fd7834ad153750c41)
