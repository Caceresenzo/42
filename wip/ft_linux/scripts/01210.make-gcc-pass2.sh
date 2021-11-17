base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh gcc

	pushd $name
		tar -xf ../mpfr-*.tar.*
		mv -v mpfr-*/ mpfr
		tar -xf ../gmp-*.tar.*
		mv -v gmp-* gmp
		tar -xf ../mpc-*.tar.*
		mv -v mpc-* mpc

		case $(uname -m) in
			x86_64) sed -e '/m64=/s/lib64/lib/' -i.orig gcc/config/i386/t-linux64 ;;
		esac

		rm -rf build
		mkdir -vp build

		pushd build
			mkdir -pv $LFS_TGT/libgcc
			ln -s ../../../libgcc/gthr-posix.h $LFS_TGT/libgcc/gthr-default.h
			
			../configure                                       \
				--build=$(../config.guess)                     \
				--host=$LFS_TGT                                \
				--prefix=/usr                                  \
				CC_FOR_TARGET=$LFS_TGT-gcc                     \
				--with-build-sysroot=$LFS                      \
				--enable-initfini-array                        \
				--disable-nls                                  \
				--disable-multilib                             \
				--disable-decimal-float                        \
				--disable-libatomic                            \
				--disable-libgomp                              \
				--disable-libquadmath                          \
				--disable-libssp                               \
				--disable-libvtv                               \
				--disable-libstdcxx                            \
				--enable-languages=c,c++

			make

			make DESTDIR=$LFS install
			
			ln -sv gcc $LFS/usr/bin/cc
		popd
	popd
popd
