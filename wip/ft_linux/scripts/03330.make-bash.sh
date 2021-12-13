chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf bash-*.tar*
cd bash-*/

./configure --prefix=/usr                      \
            --docdir=/usr/share/doc/bash-5.1.8 \
            --without-bash-malloc              \
            --with-installed-readline

make

chown -Rv tester .
su -s /usr/bin/expect tester << EOF
set timeout -1
spawn make tests
expect eof
lassign [wait] _ _ _ value
exit \$value
EOF

make install

exec /bin/bash --login +h

___END
