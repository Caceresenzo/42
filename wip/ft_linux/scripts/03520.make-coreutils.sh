chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf coreutils-*.tar*
cd coreutils-*/

patch -Np1 -i ../coreutils-*.patch

autoreconf -fiv
FORCE_UNSAFE_CONFIGURE=1 ./configure \
            --prefix=/usr            \
            --enable-no-install-program=kill,uptime

make

make NON_ROOT_USERNAME=tester check-root || true

echo "dummy:x:102:tester" >> /etc/group

chown -Rv tester .

su tester << EOF
PATH=\$PATH make RUN_EXPENSIVE_TESTS=yes check || true
EOF || true

sed -i '/dummy/d' /etc/group

make install

mv -v /usr/bin/chroot /usr/sbin
# mv -v /usr/share/man/man1/chroot.1 /usr/share/man/man8/chroot.8
# sed -i 's/"1"/"8"/' /usr/share/man/man8/chroot.8

___END
