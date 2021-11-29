chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf tcl*-src.tar*
cd tcl*/

tar -xf ../tcl*-html.tar* --strip-components=1

export SRCDIR=\$(pwd)
cd unix
./configure --prefix=/usr           \
            --mandir=/usr/share/man \
            \$([ "\$(uname -m)" = x86_64 ] && echo --enable-64bit)

make

sed -e "s|\$SRCDIR/unix|/usr/lib|" \
    -e "s|\$SRCDIR|/usr/include|"  \
    -i tclConfig.sh

sed -e "s|\$SRCDIR/unix/pkgs/tdbc1.1.2|/usr/lib/tdbc1.1.2|" \
    -e "s|\$SRCDIR/pkgs/tdbc1.1.2/generic|/usr/include|"    \
    -e "s|\$SRCDIR/pkgs/tdbc1.1.2/library|/usr/lib/tcl8.6|" \
    -e "s|\$SRCDIR/pkgs/tdbc1.1.2|/usr/include|"            \
    -i pkgs/tdbc1.1.2/tdbcConfig.sh

sed -e "s|\$SRCDIR/unix/pkgs/itcl4.2.1|/usr/lib/itcl4.2.1|" \
    -e "s|\$SRCDIR/pkgs/itcl4.2.1/generic|/usr/include|"    \
    -e "s|\$SRCDIR/pkgs/itcl4.2.1|/usr/include|"            \
    -i pkgs/itcl4.2.1/itclConfig.sh

unset SRCDIR

make test

make install

ls /usr/lib/libtcl*.so
chmod -v u+w /usr/lib/libtcl*.so

make install-private-headers

rm -rf /usr/bin/tclsh
ln -sfv \$(basename /usr/bin/tclsh*) /usr/bin/tclsh

mv /usr/share/man/man3/{Thread,Tcl_Thread}.3

___END
