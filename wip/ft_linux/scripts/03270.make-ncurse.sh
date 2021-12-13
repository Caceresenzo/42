chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf ncurses-*.tar*
cd ncurses-*/

./configure --prefix=/usr           \
            --mandir=/usr/share/man \
            --with-shared           \
            --without-debug         \
            --without-normal        \
            --enable-pc-files       \
            --enable-widec

make

make install

for lib in ncurses form panel menu ; do
    rm -vf                    /usr/lib/lib\${lib}.so
    echo "INPUT(-l\${lib}w)" > /usr/lib/lib\${lib}.so
    ln -sfv ${lib}w.pc        /usr/lib/pkgconfig/\${lib}.pc
done

rm -vf                     /usr/lib/libcursesw.so
echo "INPUT(-lncursesw)" > /usr/lib/libcursesw.so
ln -sfv libncurses.so      /usr/lib/libcurses.so

rm -fv /usr/lib/libncurses++w.a

mkdir -vp       /usr/share/doc/ncurses
cp -v -R doc/*  /usr/share/doc/ncurses

___END
