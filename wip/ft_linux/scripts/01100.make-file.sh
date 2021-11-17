base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh file
	
	pushd $name
		mkdir -vp build
		
		pushd build
			../configure               \
			    --disable-bzlib        \
				--disable-libseccomp   \
				--disable-xzlib        \
				--disable-zlib
			
			make
		popd
		
		./configure --prefix=/usr --host=$LFS_TGT --build=$(./config.guess)
		
		make FILE_COMPILE=$(pwd)/build/src/file
		
		make DESTDIR=$LFS install
	popd
popd
