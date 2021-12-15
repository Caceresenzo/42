chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf check-*.tar*
cd check-*/

./configure --prefix=/usr --disable-static

make

# hang forever...
# make check

make docdir=/usr/share/doc/check install

___END
