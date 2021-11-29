chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf binutils-*.tar*
cd binutils-*/

expect -c "spawn ls"

patch -Np1 -i ../binutils-*.patch

sed -i '63d' etc/texi2pod.pl
find -name \*.1 -delete

mkdir -vp build
cd        build

../configure --prefix=/usr       \
             --enable-gold       \
             --enable-ld=default \
             --enable-plugins    \
             --enable-shared     \
             --disable-werror    \
             --enable-64-bit-bfd \
             --with-system-zlib

make tooldir=/usr

make -k check || true

make tooldir=/usr install -j1

rm -fv /usr/lib/lib{bfd,ctf,ctf-nobfd,opcodes}.a

___END
