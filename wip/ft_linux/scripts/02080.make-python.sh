chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
cd /sources

tar xvf Python-*.tar*
cd Python-*/

./configure --prefix=/usr   \
            --enable-shared \
            --without-ensurepip

make

make install

___END
