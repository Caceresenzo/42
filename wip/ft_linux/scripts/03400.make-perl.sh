chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf perl-*.tar*
cd perl-*/

patch -Np1 -i ../perl-*.patch

export BUILD_ZLIB=False
export BUILD_BZIP2=0

sh Configure -des                                         \
             -Dprefix=/usr                                \
             -Dvendorprefix=/usr                          \
             -Dprivlib=/usr/lib/perl5/5.34/core_perl      \
             -Darchlib=/usr/lib/perl5/5.34/core_perl      \
             -Dsitelib=/usr/lib/perl5/5.34/site_perl      \
             -Dsitearch=/usr/lib/perl5/5.34/site_perl     \
             -Dvendorlib=/usr/lib/perl5/5.34/vendor_perl  \
             -Dvendorarch=/usr/lib/perl5/5.34/vendor_perl \
             -Dman1dir=/usr/share/man/man1                \
             -Dman3dir=/usr/share/man/man3                \
             -Dpager="/usr/bin/less -isR"                 \
             -Duseshrplib                                 \
             -Duseithreads

make

make test || true

make install
unset BUILD_ZLIB BUILD_BZIP2

___END
