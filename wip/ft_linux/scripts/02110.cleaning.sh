chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
rm -rf /usr/share/{info,man,doc}/*

find /usr/{lib,libexec} -name \*.la -delete

rm -rf /tools

___END

umount $LFS/dev{/pts,} || true
umount $LFS/{sys,proc,run} || true

pushd $LFS
  rm -rf $(find sources/ -maxdepth 1 -mindepth 1 -type d)
  tar cJpvf $HOME/lfs-backup.tar.xz .
popd
