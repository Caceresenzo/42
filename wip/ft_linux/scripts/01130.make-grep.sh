base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh grep
	
	pushd $name
		sed -i 's/extras//' Makefile.in
		
		./configure --prefix=/usr   \
			--host=$LFS_TGT
		
		make
		
		make DESTDIR=$LFS install
	popd
popd
