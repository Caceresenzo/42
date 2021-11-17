base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh binutils

	pushd $name
		rm -rf build
		mkdir -vp build

		pushd build
			../configure                   \
				--prefix=/usr              \
				--build=$(../config.guess) \
				--host=$LFS_TGT            \
				--disable-nls              \
				--enable-shared            \
				--disable-werror           \
				--enable-64-bit-bfd

			make

			make DESTDIR=$LFS install -j1
			install -vm755 libctf/.libs/libctf.so.0.0.0 $LFS/usr/lib
		popd
	popd
popd
