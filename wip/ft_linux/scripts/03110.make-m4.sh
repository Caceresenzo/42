chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END

cd /sources

tar xvf m4-*.tar*
cd m4-*/

./configure --prefix=/usr

make

make check

make install

___END
