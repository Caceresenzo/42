base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh patch
	
	pushd $name
		./configure --prefix=/usr   \
			--host=$LFS_TGT         \
			--build=$(build-aux/config.guess)
		
		make
		
		make DESTDIR=$LFS install
	popd
popd
