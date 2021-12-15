chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf gawk-*.tar*
cd gawk-*/

sed -i 's/extras//' Makefile.in

./configure --prefix=/usr

make

make check

make install

mkdir -vp /usr/share/doc/gawk
cp    -v  doc/{awkforai.txt,*.{eps,pdf,jpg}} /usr/share/doc/gawk

___END
