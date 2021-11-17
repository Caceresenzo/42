base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh findutils
	
	pushd $name
		./configure --prefix=/usr            \
			--localstatedir=/var/lib/locate  \
			--host=$LFS_TGT                  \
			--build=$(build-aux/config.guess)
		
		make
		
		make DESTDIR=$LFS install
	popd
popd
