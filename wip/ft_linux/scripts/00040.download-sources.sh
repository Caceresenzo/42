wget https://www.linuxfromscratch.org/lfs/view/stable/wget-list --output-document $LFS/wget-list
wget --input-file=$LFS/wget-list -nc --directory-prefix=$LFS/sources
