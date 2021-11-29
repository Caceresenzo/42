chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END

cd /sources

tar xvf zstd-*.tar*
cd zstd-*/

make

make check

make prefix=/usr install

rm -v /usr/lib/libzstd.a

___END
