chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf mpc-*.tar*
cd mpc-*/

./configure --prefix=/usr    \
            --disable-static \
            --docdir=/usr/share/doc/mpc

make
make html

make check

make install
make install-html

___END
