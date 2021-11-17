base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh xz
	
	pushd $name
		./configure --prefix=/usr             \
			--host=$LFS_TGT                   \
			--build=$(build-aux/config.guess) \
			--disable-static                  \
			--docdir=/usr/share/doc/xz-5.2.5
		
		make
		
		make DESTDIR=$LFS install
	popd
popd
