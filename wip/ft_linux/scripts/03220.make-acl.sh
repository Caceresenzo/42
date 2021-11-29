chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf acl-*.tar*
cd acl-*/

./configure --prefix=/usr         \
            --disable-static      \
            --docdir=/usr/share/doc/acl

make

make install

___END
