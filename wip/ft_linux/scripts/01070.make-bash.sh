base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh bash
	
	pushd $name
		./configure --prefix=/usr           \
			--build=$(support/config.guess) \
			--host=$LFS_TGT                 \
			--without-bash-malloc
		
		make
		
		make DESTDIR=$LFS install
		
		ln -sv bash $LFS/bin/sh
	popd
popd
