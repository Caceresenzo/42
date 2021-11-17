set +h
umask 022

LC_ALL=POSIX
LFS_TGT=$(uname -m)-lfs-linux-gnu
PATH=$LFS/tools/bin:$PATH
CONFIG_SITE=$LFS/usr/share/config.site

export LFS LC_ALL LFS_TGT PATH CONFIG_SITE

export MAKEFLAGS="-j$(nproc)"
