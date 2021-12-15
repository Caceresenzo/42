chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf automake-*.tar*
cd automake-*/

./configure --prefix=/usr --docdir=/usr/share/doc/automake

make

make -j4 check || true

make install

___END
