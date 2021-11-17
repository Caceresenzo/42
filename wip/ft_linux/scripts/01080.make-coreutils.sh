base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh coreutils
	
	pushd $name
		./configure --prefix=/usr             \
			--host=$LFS_TGT                   \
			--build=$(build-aux/config.guess) \
			--enable-install-program=hostname \
			--enable-no-install-program=kill,uptime
		
		make
		
		make DESTDIR=$LFS install
		
		mv -v $LFS/usr/bin/chroot $LFS/usr/sbin
		mkdir -pv $LFS/usr/share/man/man8
		mv -v $LFS/usr/share/man/man1/chroot.1 $LFS/usr/share/man/man8/chroot.8
		sed -i 's/"1"/"8"/' $LFS/usr/share/man/man8/chroot.8
	popd
popd
