chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf bison-*.tar*
cd bison-*/

./configure --prefix=/usr --docdir=/usr/share/doc/bison-3.7.6

make

make check

make install

___END
