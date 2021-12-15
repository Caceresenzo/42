chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf tar-*.tar*
cd tar-*/

FORCE_UNSAFE_CONFIGURE=1  \
./configure --prefix=/usr

make

make check || true

make install
make -C doc install-html docdir=/usr/share/doc/tar

___END
