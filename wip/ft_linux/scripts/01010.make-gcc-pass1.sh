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

		mkdir -vp build

		pushd build
			../configure   \
				--target=$LFS_TGT  \
				--prefix=$LFS/tools\
				--with-glibc-version=2.11  \
				--with-sysroot=$LFS\
				--with-newlib  \
				--without-headers  \
				--enable-initfini-array\
				--disable-nls  \
				--disable-shared   \
				--disable-multilib \
				--disable-decimal-float\
				--disable-threads  \
				--disable-libatomic\
				--disable-libgomp  \
				--disable-libquadmath  \
				--disable-libssp   \
				--disable-libvtv   \
				--disable-libstdcxx\
				--enable-languages=c,c++

			make

			make install
		popd

		cat gcc/limitx.h gcc/glimits.h gcc/limity.h > `dirname $($LFS_TGT-gcc -print-libgcc-file-name)`/install-tools/include/limits.h
	popd
popd
