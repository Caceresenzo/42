chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf procps-ng-*.tar*
cd procps-*/

./configure --prefix=/usr                            \
            --docdir=/usr/share/doc/procps-ng        \
            --disable-static                         \
            --disable-kill

make

make check || true

make install

___END
