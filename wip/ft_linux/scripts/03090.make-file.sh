chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END

cd /sources

tar xvf file-*.tar*
cd file-*/

./configure --prefix=/usr

make

make check

make install

___END
