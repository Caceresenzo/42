base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh binutils
	echo $name $archive
	echo -------------------

	pushd $name
		mkdir -vp build

		pushd build
			../configure --prefix=$LFS/tools \
				--with-sysroot=$LFS \
				--target=$LFS_TGT \
				--disable-nls \
				--disable-werror

			make

			make install -j1
		popd
	popd
popd
