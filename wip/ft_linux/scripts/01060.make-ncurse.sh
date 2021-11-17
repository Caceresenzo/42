base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh ncurses
	
	pushd $name
		rm -rf build
		mkdir -vp build
		
		sed -i s/mawk// configure

		pushd build
			../configure
			
			make -C include
			make -C progs tic
		popd
		
		./configure --prefix=/usr        \
			--host=$LFS_TGT              \
			--build=$(./config.guess)    \
			--mandir=/usr/share/man      \
			--with-manpage-format=normal \
			--with-shared                \
			--without-debug              \
			--without-ada                \
			--without-normal             \
			--enable-widec
			
		make
		
		make DESTDIR=$LFS TIC_PATH=$(pwd)/build/progs/tic install
		
		echo "INPUT(-lncursesw)" > $LFS/usr/lib/libncurses.so
	popd
popd
