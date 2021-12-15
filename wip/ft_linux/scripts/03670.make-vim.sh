chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/usr/bin:/usr/sbin     \
    /bin/bash --login +h        \
    << ___END
set -e

cd /sources

tar xvf vim-*.tar*
cd vim-*/

echo '#define SYS_VIMRC_FILE "/etc/vimrc"' >> src/feature.h

./configure --prefix=/usr

make

chown -Rv tester .
su tester << EOF
LANG=en_US.UTF-8 make -j1 test || true
EOF

make install

rm -f /usr/bin/vi
ln -sv vim /usr/bin/vi

for L in /usr/share/man/{,*/}man1/vim.1; do
    rm -f \$(dirname \$L)/vi.1
    ln -sv vim.1 \$(dirname \$L)/vi.1
done

ln -sv ../vim/vim82/doc /usr/share/doc/vim

cat > /etc/vimrc << "EOF"
" Begin /etc/vimrc

" Ensure defaults are set before customizing settings, not after
source \$VIMRUNTIME/defaults.vim
let skip_defaults_vim=1 

set nocompatible
set backspace=2
set mouse=
syntax on
if (&term == "xterm") || (&term == "putty")
  set background=dark
endif

" End /etc/vimrc
EOF

___END
