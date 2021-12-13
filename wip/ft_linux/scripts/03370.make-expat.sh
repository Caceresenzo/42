chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf expat-*.tar*
cd expat-*/

./configure --prefix=/usr    \
            --disable-static \
            --docdir=/usr/share/doc/expat

make

make check

make install

install -v -m644 doc/*.{html,png,css} /usr/share/doc/expat

___END
