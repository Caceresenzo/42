chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf iproute2-*.tar*
cd iproute2-*/

sed -i /ARPD/d Makefile
rm -fv man/man8/arpd.8

sed -i 's/.m_ipt.o//' tc/Makefile

make

make SBINDIR=/usr/sbin install

mkdir -vp              /usr/share/doc/iproute2
cp -v COPYING README*  /usr/share/doc/iproute2

___END
