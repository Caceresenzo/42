chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf findutils-*.tar*
cd findutils-*/

./configure --prefix=/usr --localstatedir=/var/lib/locate

make

chown -Rv tester .
su tester << EOF
PATH=\$PATH make check
EOF

make install

___END