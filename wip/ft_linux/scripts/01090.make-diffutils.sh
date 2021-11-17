base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh diffutils
	
	pushd $name
		./configure --prefix=/usr --host=$LFS_TGT
		
		make
		
		make DESTDIR=$LFS install
	popd
popd
