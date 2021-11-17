export LSF_WGET_LIST="https://www.linuxfromscratch.org/lfs/view/stable/wget-list"

wget $LSF_WGET_LIST --output-document $LFS/wget-list
