export LSF_MD5SUMS_URL="https://www.linuxfromscratch.org/lfs/view/stable/md5sums"
export LSF_MD5SUMS_FILE="$LFS/md5sums"

wget $LSF_MD5SUMS_URL --output-document $LSF_MD5SUMS_FILE
