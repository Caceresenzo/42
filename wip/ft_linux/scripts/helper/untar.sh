package=$1
shift

archive=$(basename $package-*.tar.*)

tar --skip-old-files -x -v -f $archive $@

name=$(echo $package-*/)
