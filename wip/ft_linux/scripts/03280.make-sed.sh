chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf sed-*.tar*
cd sed-*/

./configure --prefix=/usr

make
make html

chown -Rv tester .
su tester << EOF
PATH=\$PATH make check
EOF

make install
install -d -m755           /usr/share/doc/sed
install -m644 doc/sed.html /usr/share/doc/sed

___END
