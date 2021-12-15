chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf eudev-*.tar*
cd eudev-*/

./configure --prefix=/usr           \
            --bindir=/usr/sbin      \
            --sysconfdir=/etc       \
            --enable-manpages       \
            --disable-static

make

mkdir -pv /usr/lib/udev/rules.d
mkdir -pv /etc/udev/rules.d

# hangs forver...
# make check

make install

tar -xvf ../udev-lfs-*.tar*
make -f udev-lfs-*/Makefile.lfs install

udevadm hwdb --update

___END
