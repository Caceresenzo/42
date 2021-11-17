base=$(pwd)

pushd $LFS/sources
	#rm -rf gcc-*/
	. $base/$(dirname $0)/helper/untar.sh gcc
	
	pushd $name
		rm -rf build
		mkdir -vp build

		pushd build
			../libstdc++-v3/configure           \
				--host=$LFS_TGT                 \
				--build=$(../config.guess)      \
				--prefix=/usr                   \
				--disable-multilib              \
				--disable-nls                   \
				--disable-libstdcxx-pch         \
				--with-gxx-include-dir=/tools/$LFS_TGT/include/c++/11.2.0

			make

			make DESTDIR=$LFS install
		popd
	popd
popd
