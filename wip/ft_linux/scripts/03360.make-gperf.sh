chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf gperf-*.tar*
cd gperf-*/

./configure --prefix=/usr --docdir=/usr/share/doc/gperf

make

make -j1 check

make install

___END
