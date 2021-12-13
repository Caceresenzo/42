chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf gdbm-*.tar*
cd gdbm-*/

./configure --prefix=/usr    \
            --disable-static \
            --enable-libgdbm-compat

make

make -k check || true

make install

___END