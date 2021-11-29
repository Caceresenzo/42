chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END

cd /sources/glibc-*/build

cat > /etc/nsswitch.conf << "EOF"
# Begin /etc/nsswitch.conf

passwd: files
group: files
shadow: files

hosts: files dns
networks: files

protocols: files
services: files
ethers: files
rpc: files

# End /etc/nsswitch.conf
EOF

tar -xf ../../tzdata*.tar*

export ZONEINFO=/usr/share/zoneinfo
mkdir -pv \$ZONEINFO/{posix,right}

for tz in etcetera southamerica northamerica europe africa antarctica  \
          asia australasia backward; do
    zic -L /dev/null   -d \$ZONEINFO       \${tz}
    zic -L /dev/null   -d \$ZONEINFO/posix \${tz}
    zic -L leapseconds -d \$ZONEINFO/right \${tz}
done

cp -v zone.tab zone1970.tab iso3166.tab \$ZONEINFO
zic -d \$ZONEINFO -p America/New_York
unset ZONEINFO

# tzselect

ln -sfv /usr/share/zoneinfo/America/Edmonton /etc/localtime

cat > /etc/ld.so.conf << "EOF"
# Begin /etc/ld.so.conf
/usr/local/lib
/opt/lib

EOF

cat >> /etc/ld.so.conf << "EOF"
# Add an include directory
include /etc/ld.so.conf.d/*.conf

EOF
mkdir -pv /etc/ld.so.conf.d

___END
